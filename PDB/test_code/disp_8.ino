//code that deals with displaying the data to the outside world.

#include <SevenSeg.h>


//Segment Pins, A toG then decimal pt.
SevenSeg disp(8,9,7,2,0,15,14);

const int numOfDigits=4;
int digitPins[numOfDigits] = {6, 5, 4, 3};


unsigned long last_LED_time = 0;  //Time the last LED switched
int sequence = 0; //used to switch states for the display.  Remember that the hangle_8_segment cannot be blocking.

int segment_8_run = 0;  //0 for the normal voltage readout.  1 for "Clear Calibration".  2 for "New Calibration"

void setup_display()
{
  disp.setDigitPins(numOfDigits,digitPins);
  disp.setDPPin(1);  //set the Decimal Point pin to #1   
}




void handle_8_segment() //handles the 8-segment display, and prints out the global values.
//MUST be called in the loop() without any if's
{
  if(segment_8_run == 0)
  {
    //Shows text / numbers of all voltages & then individual cells.
    //Changed every Second
    if(sequence == 0)
    {
      disp.write("ALL");
    }
    else if(sequence == 1)
    {
      disp.write(v_batt,2);
    }
    else if(sequence == 2)
    {
      disp.write("CEL.1"); 
    }
    else if(sequence == 3)
    {
      disp.write(v_cell1,2);
    }
    else if(sequence == 4)
    {
      disp.write("CEL.2"); 
    }
    else if(sequence == 5)
    {
      disp.write(dv_cell2,2);
    }
    else if(sequence == 6)
    {
      disp.write("CEL.3"); 
    }
    else if(sequence == 7)
    {
      disp.write(dv_cell3,2);
    }
    
    if (millis() > (last_LED_time + 1000) ) //every second
    {
      sequence = sequence + 1;
      if(sequence == 8)
      {
        sequence=0;
      }
      last_LED_time = millis();
    }
  }
  else if(segment_8_run == 1)
  {
    if(sequence == 0)
    {    
      disp.write("CAL");
    }
    else if(sequence == 1)
    {
      disp.write("CLR");
    }

    if (millis() > (last_LED_time + 750) ) //every 3/4 second
    {
      sequence = sequence + 1;
      if(sequence == 2)
      {
        start_8_seg_sequence(0); //return to default Programming... showing battery voltages.
      }
      last_LED_time = millis();
    }

  }
  else if(segment_8_run == 2)
  {
    if(sequence == 0)
    {
      disp.write("CAL");
    }
    else if(sequence == 1)
    {
      disp.write("DONE");      
    }
    if(sequence == 2)
    {
      disp.write("CAL");
    }
    if(sequence == 3)
    {
      disp.write(vref_guess,3);
    }
    /*
    if(sequence == 4)
    {
      disp.write("CAL.2");
    }
    if(sequence == 5)
    {
      disp.write(vref_guess,3);
    }
    if(sequence == 6)
    {
      disp.write("CAL.3");
    }
    if(sequence == 7)
    {
      disp.write(vref_guess,3);
    }
    */

    if (millis() > (last_LED_time + 750) ) //every 3/4 second
    {
      sequence = sequence + 1;
      if(sequence == 4)
      {
        start_8_seg_sequence(0); //return to default Programming... showing battery voltages.
      }
      last_LED_time = millis();
    }
    
  }
  
}

void start_8_seg_sequence(int sequence_num)
{
  segment_8_run = sequence_num; //rel the display to run the right sequence
  sequence = 0;  //and reset the step in the sequence to zero.
  last_LED_time = millis();
}

