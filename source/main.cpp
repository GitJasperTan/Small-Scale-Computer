#include <cstdint>
#include "Bus.hpp"
Bus bus;
void keyboard_interrupt();

uint8_t command_register = 0xf3;
uint8_t data_setmode_0   = 0x82;
uint8_t addr_port_A      = 0xf0;
uint8_t data_port_A      = 0x0f;  // initialize to 0000 1111
uint8_t addr_port_B      = 0xf1;

int main()
{
	

  //Bus Initialize
  bus.Initialize();
  sjsu::lpc40xx::Gpio interrupt = sjsu::lpc40xx::Gpio(0, 11);

  //82C55 Initialize
  bus.IOWrite(command_register, data_setmode_0);
  bus.IOWrite(addr_port_A, data_port_A);


  //Interrupt
  interrupt.GetPin().SetPull(sjsu::Pin::Resistor::kPullUp);
  interrupt.AttachInterrupt(keyboard_interrupt, sjsu::Gpio::Edge::kEdgeRising);

  while (1)
  {
    // empty
    LOG_INFO("Waiting for Interrupt\n");
    sjsu::Delay(500ms);
  }

  return 0;
}

void keyboard_interrupt()
{
  LOG_INFO("\nKey detected\n\n");

  for (int i = 1; i <= 4; i++)
  {
    switch (i)
    {
      case 1:
        data_port_A = 0x01;
        bus.IOWrite(addr_port_A, data_port_A);
        if (bus.IORead(addr_port_B) == 0xf1)
        {
          LOG_INFO("Key pressed: 1\n");
        }
        else if (bus.IORead(addr_port_B) == 0xf2)
        {
          LOG_INFO("Key pressed: 2\n");
        }
        else if (bus.IORead(addr_port_B) == 0xf4)
        {
          LOG_INFO("Key pressed: 3\n");
        }
        else if (bus.IORead(addr_port_B) == 0xf8)
        {
          LOG_INFO("Key pressed: A\n");
        }
        break;

      case 2:
        data_port_A = 0x02;
        bus.IOWrite(addr_port_A, data_port_A);
        if (bus.IORead(addr_port_B) == 0xf1)
        {
          LOG_INFO("Key pressed: 4\n");
        }
        else if (bus.IORead(addr_port_B) == 0xf2)
        {
          LOG_INFO("Key pressed: 5\n");
        }
        else if (bus.IORead(addr_port_B) == 0xf4)
        {
          LOG_INFO("Key pressed: 6\n");
        }
        else if (bus.IORead(addr_port_B) == 0xf8)
        {
          LOG_INFO("Key pressed: B\n");
        }
        break;

      case 3:
        data_port_A = 0x04;
        bus.IOWrite(addr_port_A, data_port_A);
        if (bus.IORead(addr_port_B) == 0xf1)
        {
          LOG_INFO("Key pressed: 7\n");
        }
        else if (bus.IORead(addr_port_B) == 0xf2)
        {
          LOG_INFO("Key pressed: 8\n");
        }
        else if (bus.IORead(addr_port_B) == 0xf4)
        {
          LOG_INFO("Key pressed: 9\n");
        }
        else if (bus.IORead(addr_port_B) == 0xf8)
        {
          LOG_INFO("Key pressed: C\n");
        }
        break;

      case 4:
        data_port_A = 0x08;
        bus.IOWrite(addr_port_A, data_port_A);
        if (bus.IORead(addr_port_B) == 0xf1)
        {
          LOG_INFO("Key pressed: *\n");
        }
        else if (bus.IORead(addr_port_B) == 0xf2)
        {
          LOG_INFO("Key pressed: 0\n");
        }
        else if (bus.IORead(addr_port_B) == 0xf4)
        {
          LOG_INFO("Key pressed: #\n");
        }
        else if (bus.IORead(addr_port_B) == 0xf8)
        {
          LOG_INFO("Key pressed: D\n");
        }
        break;
    }
  }
  data_port_A = 0x0f;
  bus.IOWrite(addr_port_A, data_port_A);
    
  
}


























// while (true)
//{
//  for (int i = 1; i <= 4; i++)
//  {
//    switch (i)
//    {
//      case 1:
//        data_port_A = 0x01;
//        bus.IOWrite(addr_port_A, data_port_A);
//        if (bus.IORead(addr_port_B) == 0xf1)
//        {
//          LOG_INFO("Key pressed: 1\n");
//        }
//        else if (bus.IORead(addr_port_B) == 0xf2)
//        {
//          LOG_INFO("Key pressed: 2\n");
//        }
//        else if (bus.IORead(addr_port_B) == 0xf4)
//        {
//          LOG_INFO("Key pressed: 3\n");
//        }
//        else if (bus.IORead(addr_port_B) == 0xf8)
//        {
//          LOG_INFO("Key pressed: A\n");
//        }
//        break;
//
//      case 2:
//        data_port_A = 0x02;
//        bus.IOWrite(addr_port_A, data_port_A);
//        if (bus.IORead(addr_port_B) == 0xf1)
//        {
//          LOG_INFO("Key pressed: 4\n");
//        }
//        else if (bus.IORead(addr_port_B) == 0xf2)
//        {
//          LOG_INFO("Key pressed: 5\n");
//        }
//        else if (bus.IORead(addr_port_B) == 0xf4)
//        {
//          LOG_INFO("Key pressed: 6\n");
//        }
//        else if (bus.IORead(addr_port_B) == 0xf8)
//        {
//          LOG_INFO("Key pressed: B\n");
//        }
//        break;
//
//      case 3:
//        data_port_A = 0x04;
//        bus.IOWrite(addr_port_A, data_port_A);
//        if (bus.IORead(addr_port_B) == 0xf1)
//        {
//          LOG_INFO("Key pressed: 7\n");
//        }
//        else if (bus.IORead(addr_port_B) == 0xf2)
//        {
//          LOG_INFO("Key pressed: 8\n");
//        }
//        else if (bus.IORead(addr_port_B) == 0xf4)
//        {
//          LOG_INFO("Key pressed: 9\n");
//        }
//        else if (bus.IORead(addr_port_B) == 0xf8)
//        {
//          LOG_INFO("Key pressed: C\n");
//        }
//        break;
//
//      case 4:
//        data_port_A = 0x08;
//        bus.IOWrite(addr_port_A, data_port_A);
//        if (bus.IORead(addr_port_B) == 0xf1)
//        {
//          LOG_INFO("Key pressed: *\n");
//        }
//        else if (bus.IORead(addr_port_B) == 0xf2)
//        {
//          LOG_INFO("Key pressed: 0\n");
//        }
//        else if (bus.IORead(addr_port_B) == 0xf4)
//        {
//          LOG_INFO("Key pressed: #\n");
//        }
//        else if (bus.IORead(addr_port_B) == 0xf8)
//        {
//          LOG_INFO("Key pressed: D\n");
//        }
//        break;
//
//        sjsu::Delay(500ms);
//    }
//  }
//}
