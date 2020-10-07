#include <cstdint>
#include "L1_Peripheral/lpc40xx/gpio.hpp"
#include "utility//time.hpp"

class Bus
{
 public:
  void Initialize()
  {
    // Setting each pin as Open Drain
    ad[0].GetPin().SetAsOpenDrain();
    ad[1].GetPin().SetAsOpenDrain();
    ad[2].GetPin().SetAsOpenDrain();
    ad[3].GetPin().SetAsOpenDrain();
    ad[4].GetPin().SetAsOpenDrain();
    ad[5].GetPin().SetAsOpenDrain();
    ad[6].GetPin().SetAsOpenDrain();
    ad[7].GetPin().SetAsOpenDrain();
    write_enable.SetAsOutput();
    ale.SetAsOutput();
    m_io.SetAsOutput();
    write.SetAsOutput();
    read.SetAsOutput();
    interrupt.SetAsInput();

    ad[0].SetAsOutput();
    ad[1].SetAsOutput();
    ad[2].SetAsOutput();
    ad[3].SetAsOutput();
    ad[4].SetAsOutput();
    ad[5].SetAsOutput();
    ad[6].SetAsOutput();
    ad[7].SetAsOutput();

	//Memory Initialization
    write_enable.SetHigh();
    ale.SetLow();
    write.SetHigh();
    read.SetLow();
    m_io.SetHigh();

	//IO Initialization

  }

  void MemWrite(uint8_t address, uint8_t data)
  {
    ale.SetHigh();
    write_enable.SetHigh();
    read.SetHigh();
    write.SetHigh();
    m_io.SetHigh();
    //sjsu::Delay(1s);

    for (int i = 0; i < 8; i++)
    {
      ad[i].SetAsOutput();
      if (address & (1 << i))
      {
        ad[i].SetHigh();
      }
      else
      {
        ad[i].SetLow();
      }
    }

    //sjsu::Delay(1s);
    ale.SetLow();
    //sjsu::Delay(1s);

    for (int i = 0; i < 8; i++)
    {
      if (data & (1 << i))
      {
        ad[i].SetHigh();
      }
      else
      {
        ad[i].SetLow();
      }
    }

    write.SetLow();
    //sjsu::Delay(1s);
    write.SetHigh();
    //sjsu::Delay(1s);
  }

  uint8_t MemRead(uint8_t address)
  {
    uint8_t temp = 0;

    ale.SetHigh();
    write_enable.SetHigh();
    read.SetHigh();
    write.SetHigh();
    m_io.SetHigh();
    //sjsu::Delay(1s);

    for (int i = 0; i < 8; i++)
    {
      if (address & (1 << i))
      {
        ad[i].SetHigh();
      }
      else
      {
        ad[i].SetLow();
      }
    }

    //sjsu::Delay(1s);
    ale.SetLow();
    //sjsu::Delay(1s);

    for (int i = 0; i < 8; i++)
    {
      ad[i].SetAsInput();
    }

    write_enable.SetLow();
    read.SetLow();
    //sjsu::Delay(1s);

    temp = 0;
    for (int i = 0; i < 8; i++)
    {
      temp = temp | (ad[i].Read() << i);
	}

    //sjsu::Delay(1s);
    write_enable.SetHigh();
    read.SetHigh();
    //sjsu::Delay(1s);

	for (int i = 0; i < 8; i++)
    {
          ad[i].SetAsOutput();
	}
    //sjsu::Delay(1s);

	return temp;
  }
  void IOWrite(uint8_t address, uint8_t data)
  {
	ale.SetHigh();
    write_enable.SetHigh();
    read.SetHigh();
    write.SetHigh();
    m_io.SetLow();
    //sjsu::Delay(1ms);

	for (int i = 0; i < 8; i++)
    {
      ad[i].SetAsOutput();
      if (address & (1 << i))
      {
        ad[i].SetHigh();
      }
      else
      {
        ad[i].SetLow();
      }
    }

    //sjsu::Delay(1ms);
    ale.SetLow();
    //sjsu::Delay(1ms);

	for (int i = 0; i < 8; i++)
    {
      if (data & (1 << i))
      {
        ad[i].SetHigh();
      }
      else
      {
        ad[i].SetLow();
      }
    }

	write.SetLow();
    //sjsu::Delay(1ms);
    write.SetHigh();
    //sjsu::Delay(1ms);




  }

  uint8_t IORead(uint8_t address)
  {
    uint8_t temp = 0;

    ale.SetHigh();
    write_enable.SetHigh();
    read.SetHigh();
    write.SetHigh();
    m_io.SetLow();
    //sjsu::Delay(1ms);

    for (int i = 0; i < 8; i++)
    {
      if (address & (1 << i))
      {
        ad[i].SetHigh();
      }
      else
      {
        ad[i].SetLow();
      }
    }

    //sjsu::Delay(1ms);
    ale.SetLow();
    //sjsu::Delay(1ms);

    for (int i = 0; i < 8; i++)
    {
      ad[i].SetAsInput();
    }

    write_enable.SetLow();
    read.SetLow();
    //sjsu::Delay(1ms);

    temp = 0;
    for (int i = 0; i < 8; i++)
    {
      temp = temp | (ad[i].Read() << i);
    }

    //sjsu::Delay(1ms);
    write_enable.SetHigh();
    read.SetHigh();
    //sjsu::Delay(1ms);

    for (int i = 0; i < 8; i++)
    {
      ad[i].SetAsOutput();
    }
    //sjsu::Delay(1ms);

    return temp;
  }

 private:
  sjsu::lpc40xx::Gpio ad[8] = {
    sjsu::lpc40xx::Gpio(2, 2),  sjsu::lpc40xx::Gpio(2, 5),
    sjsu::lpc40xx::Gpio(2, 7),  sjsu::lpc40xx::Gpio(2, 9),
    sjsu::lpc40xx::Gpio(0, 15), sjsu::lpc40xx::Gpio(0, 18),
    sjsu::lpc40xx::Gpio(0, 1),  sjsu::lpc40xx::Gpio(0, 10),
  };

  sjsu::lpc40xx::Gpio write_enable = sjsu::lpc40xx::Gpio(0, 17);
  sjsu::lpc40xx::Gpio ale          = sjsu::lpc40xx::Gpio(0, 22);
  sjsu::lpc40xx::Gpio m_io         = sjsu::lpc40xx::Gpio(0, 0);
  sjsu::lpc40xx::Gpio interrupt    = sjsu::lpc40xx::Gpio(0, 11);
  sjsu::lpc40xx::Gpio write        = sjsu::lpc40xx::Gpio(0, 16);
  sjsu::lpc40xx::Gpio read         = sjsu::lpc40xx::Gpio(2, 8);
};