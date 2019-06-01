#include <mcal_gpt.h>
#include <mcal_reg_access.h>

namespace
{
  volatile mcal::i2c::value_type br;
  volatile mcal::i2c::value_type bs;

  bool& i2c_is_initialized()
  {
    static bool is_init;

    return is_init;
  }
}

//Compliant bus with TWI. Two ports are used, SCL (PB0) and SDA (PB2).
//USIBR & USIDR, contain the data. Both are accessible but
// USIBR includes a copy of USIDR.

/*
 * To Communicate we need to use a timer to control the usiclk.
**/
void mcal::i2c::init(const config_type*)
{
  if (gpt_is_initialized () == false)
    {
      //Set the portb direction. 
      mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::portb, 0x05U>::reg_or();
      mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::ddrb, 0x05U>::reg_or();

      //Set the Two Wire Mode: 0x30
      mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::usicr, 0x22U>::reg_set();
    }
}
