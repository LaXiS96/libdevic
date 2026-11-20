#include <libdevic/port/ch32v003.h>

void devic_i2c_init(devic_i2c_remap_t remap, uint32_t clock)
{
    uint32_t periph = 0;
    uint16_t pin = 0;
    switch (remap)
    {
    case DEVIC_I2C_REMAP_0:
        periph = RCC_APB2Periph_GPIOC;
        pin = GPIO_Pin_1 | GPIO_Pin_2;
        break;
    case DEVIC_I2C_REMAP_1:
        periph = RCC_APB2Periph_GPIOD;
        pin = GPIO_Pin_0 | GPIO_Pin_1;
        break;
    case DEVIC_I2C_REMAP_2:
        periph = RCC_APB2Periph_GPIOC;
        pin = GPIO_Pin_5 | GPIO_Pin_6;
        break;
    }
    RCC_APB2PeriphClockCmd(periph | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_Init(GPIOC, &(GPIO_InitTypeDef){
                         .GPIO_Pin = pin,
                         .GPIO_Mode = GPIO_Mode_AF_OD,
                         .GPIO_Speed = GPIO_Speed_30MHz,
                     });

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    I2C_Init(I2C1, &(I2C_InitTypeDef){
                       .I2C_Ack = I2C_Ack_Enable,
                       .I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit,
                       .I2C_ClockSpeed = clock,
                       .I2C_DutyCycle = I2C_DutyCycle_2,
                       .I2C_Mode = I2C_Mode_I2C,
                   });
    I2C_Cmd(I2C1, ENABLE);
}

static devic_err_t check_errors(void)
{
    if (I2C_GetFlagStatus(I2C1, I2C_FLAG_AF))
    {
        I2C_GenerateSTOP(I2C1, ENABLE);
        I2C_ClearFlag(I2C1, I2C_FLAG_AF);
        return DEVIC_ERR_I2C_NACK;
    }
    if (I2C_GetFlagStatus(I2C1, I2C_FLAG_BERR))
    {
        I2C_GenerateSTOP(I2C1, ENABLE);
        I2C_ClearFlag(I2C1, I2C_FLAG_BERR);
        return DEVIC_ERR_I2C_BUS_ERROR;
    }
    if (I2C_GetFlagStatus(I2C1, I2C_FLAG_ARLO))
    {
        I2C_ClearFlag(I2C1, I2C_FLAG_ARLO);
        return DEVIC_ERR_I2C_ARBITRATION_LOST;
    }
    if (I2C_GetFlagStatus(I2C1, I2C_FLAG_OVR))
    {
        // Note: should never happen in master mode
        return DEVIC_ERR_I2C_OVERRUN;
    }
    return DEVIC_OK;
}

static devic_err_t wait_event(uint32_t event)
{
    uint32_t start = devic_time_ms;
    while (!I2C_CheckEvent(I2C1, event))
    {
        devic_err_return(check_errors());
        if (devic_time_ms - start >= I2C_TIMEOUT_MS)
            // TODO do we need to do anything to ensure the next transaction can start?
            return DEVIC_ERR_TIMEOUT;
    }
    return DEVIC_OK;
}

static devic_err_t wait_flag(uint32_t flag, FlagStatus expected)
{
    uint32_t start = devic_time_ms;
    while (I2C_GetFlagStatus(I2C1, flag) != expected)
    {
        devic_err_return(check_errors());
        if (devic_time_ms - start >= I2C_TIMEOUT_MS)
            return DEVIC_ERR_TIMEOUT;
    }
    return DEVIC_OK;
}

devic_err_t devic_i2c_transfer(devic_i2c_t *dev, uint8_t address, const uint8_t *write_buf, size_t write_len, uint8_t *read_buf, size_t read_len)
{
    return devic_i2c_transferv(dev, address,
                               (devic_i2c_buffer_t[]){{.data = write_buf, .length = write_len}}, 1,
                               read_buf, read_len);
}

devic_err_t devic_i2c_transferv(devic_i2c_t *dev, uint8_t address, const devic_i2c_buffer_t *write_bufs, size_t write_len, uint8_t *read_buf, size_t read_len)
{
    devic_err_return(wait_flag(I2C_FLAG_BUSY, RESET));

    if (write_bufs != NULL && write_len > 0)
    {
        I2C_GenerateSTART(I2C1, ENABLE);
        devic_err_return(wait_event(I2C_EVENT_MASTER_MODE_SELECT)); // EVT5

        I2C_Send7bitAddress(I2C1, address << 1, I2C_Direction_Transmitter);
        devic_err_return(wait_event(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); // EVT6

        for (size_t n = 0; n < write_len; n++)
        {
            const devic_i2c_buffer_t *buf = write_bufs + n;
            size_t i = 0;
            I2C_SendData(I2C1, buf->data[i++]); // EVT8_1
            while (i < buf->length)
            {
                devic_err_return(wait_event(I2C_EVENT_MASTER_BYTE_TRANSMITTING)); // EVT8
                I2C_SendData(I2C1, buf->data[i++]);
            }
        }

        devic_err_return(wait_event(I2C_EVENT_MASTER_BYTE_TRANSMITTED)); // EVT8_2
    }

    if (read_buf == NULL || read_len == 0)
    {
        I2C_GenerateSTOP(I2C1, ENABLE);
        return DEVIC_OK;
    }

    I2C_GenerateSTART(I2C1, ENABLE);
    devic_err_return(wait_event(I2C_EVENT_MASTER_MODE_SELECT)); // EVT5

    if (read_len == 2)
        I2C_NACKPositionConfig(I2C1, I2C_NACKPosition_Next);
    else
        I2C_NACKPositionConfig(I2C1, I2C_NACKPosition_Current);

    I2C_AcknowledgeConfig(I2C1, ENABLE);

    I2C_Send7bitAddress(I2C1, address << 1, I2C_Direction_Receiver);
    devic_err_return(wait_event(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); // EVT6

    if (read_len == 1)
    {
        I2C_AcknowledgeConfig(I2C1, DISABLE); // EVT6_1
        I2C_GenerateSTOP(I2C1, ENABLE);
        devic_err_return(wait_flag(I2C_FLAG_RXNE, SET));
        *read_buf = I2C_ReceiveData(I2C1);
    }
    else if (read_len == 2)
    {
        // Thank you WCH for not properly documenting the 2-byte read sequence
        I2C_AcknowledgeConfig(I2C1, DISABLE);
        devic_err_return(wait_flag(I2C_FLAG_RXNE | I2C_FLAG_BTF, SET));
        I2C_GenerateSTOP(I2C1, ENABLE);
        *read_buf = I2C_ReceiveData(I2C1);
        *(read_buf + 1) = I2C_ReceiveData(I2C1);
    }
    else
        // TODO it looks like we still read (but discard) one additional byte sometimes
        for (size_t i = 0; i < read_len; i++)
        {
            devic_err_return(wait_event(I2C_EVENT_MASTER_BYTE_RECEIVED)); // EVT7
            if (i + 2 == read_len)
            {
                I2C_AcknowledgeConfig(I2C1, DISABLE); // EVT7_1
                I2C_GenerateSTOP(I2C1, ENABLE);
            }
            *read_buf++ = I2C_ReceiveData(I2C1);
        }

    return DEVIC_OK;
}
