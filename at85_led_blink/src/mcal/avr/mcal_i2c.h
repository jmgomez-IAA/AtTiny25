#ifndef _MCAL_GPT_2011_10_20_H_
  #define _MCAL_GPT_2011_10_20_H_

#include <avr/interrupt.h>
#include <cstdint>

#include <mcal.h>

namespace mcal
{
  namespace usi 
  {
    typedef void config_type;
    typedef std::uint32_t value_type;

    void init(const config_type*);
  }

}
