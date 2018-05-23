///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//


//mcal reg for attiny85
#ifndef _MCAL_REG_2010_04_10_H_
  #define _MCAL_REG_2010_04_10_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      constexpr std::uint8_t sfr_offset = 0x20U;

      // Bit-position values.
      constexpr std::uint8_t bval0  = 1U;
      constexpr std::uint8_t bval1  = 1U << 1U;
      constexpr std::uint8_t bval2  = 1U << 2U;
      constexpr std::uint8_t bval3  = 1U << 3U;
      constexpr std::uint8_t bval4  = 1U << 4U;
      constexpr std::uint8_t bval5  = 1U << 5U;
      constexpr std::uint8_t bval6  = 1U << 6U;
      constexpr std::uint8_t bval7  = 1U << 7U;

      // Port registers
      constexpr std::uint8_t ddrb   = 0x17U + sfr_offset;
      constexpr std::uint8_t portb  = 0x18U + sfr_offset;

      // Timer registers
      constexpr std::uint8_t gtccr  = 0x2CU + sfr_offset;
      constexpr std::uint8_t tifr0  = 0x38U + sfr_offset;
      constexpr std::uint8_t tccr0a = 0x2AU + sfr_offset;
      constexpr std::uint8_t tccr0b = 0x33U + sfr_offset;
      constexpr std::uint8_t tcnt0  = 0x32U + sfr_offset;
      constexpr std::uint8_t ocr0a  = 0x29U + sfr_offset;
      constexpr std::uint8_t ocr0b  = 0x28U + sfr_offset;
      constexpr std::uint8_t timsk0 = 0x39U + sfr_offset;

      // USI registers
      constexpr std::uint8_t usidr = 0x0FU + sfr_offset;
      constexpr std::uint8_t usibr = 0x10U + sfr_offset;
      constexpr std::uint8_t usisr = 0x0EU + sfr_offset;
      constexpr std::uint8_t usicr = 0x0DU + sfr_offset;
      
    }
  }
#endif // _MCAL_REG_2010_04_10_H_
