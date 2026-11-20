#pragma once

/** Bit Set Masked: sets `bits` at offset `shift` in `target` after clearing them */
#define devic_bsm(target, shift, mask, bits) ((target) = ((target) & ~((mask) << (shift))) | (((bits) & (mask)) << (shift)))

/** Converts two bytes into an unsigned 16bit value */
#define devic_u8_to_u16(msb, lsb) ((uint16_t)(msb) << 8 | (lsb))

/** Converts an unsigned 16bit value into big endian bytes */
#define devic_u16_be(v) (uint8_t)((v) >> 8), (uint8_t)(v)

/** Returns the absolute value of int32_t as uint32_t */
static inline uint32_t devic_abs_u32(int32_t value)
{
    uint32_t u = (uint32_t)value;
    return value < 0 ? 0U - u : u;
}
