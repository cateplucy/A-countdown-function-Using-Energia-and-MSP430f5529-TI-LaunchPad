

String inputString = ""; // a string to hold incoming data
int inputN=0;
boolean stringComplete = false; // whether the string is complete
boolean validNumeric = true;
boolean flag1=false;//whether the input string is completed
int Kcount=0;
int Mcount;
boolean pause_flag;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  Serial.println("Enter an interger between 5 and 20:");
}

void loop() {
// print the string when a newline arrives:

if (stringComplete) {//if string is entered 
Serial.println(inputString); 
  if(flag1==0){
  //check if it is neumarical value
  //call fnc isValidNumber to check
  validNumeric = isValidNumber(inputString);
    if(validNumeric == true){
    inputN = inputString.toInt();
     if (inputN>20||inputN<5){
     Serial.println("Try again") ;
      }
      else if(inputN<=20&&inputN>=5){
      Kcount=inputN;
      flag1=1;//flag to keep counting down
      Serial.print("\nStart count down \t");
      }
      
    }else{
          if (inputString=="pause"){
          pause_flag=1;
          Mcount=Kcount;
            if (Kcount==0){
            Serial.print("\nNo count down in progress");
            }
          }
          
          if (inputString=="resume"){
            pause_flag=0;
            Kcount=Mcount;
              if (Kcount==0){
              Serial.print("\nNo count down in progress");
              }
          }
          
          if (inputString=="restart"){
           pause_flag=0;
           Kcount=inputN; 
          }
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
   
  }//end if stringcomplete
}

  if (flag1==1){   
    if(pause_flag==0){
    Serial.println(Kcount); 
      if(Kcount>0){ 
        Kcount=Kcount-1;
        delay(1000);
        }else{
        flag1=0;
        }       
}
else if(pause_flag==1){
      Mcount=Kcount;
    }
}
}

//check if string is numeric 
 boolean isValidNumber(String inputString){
 for(byte i=0;i<inputString.length();i++){
   if(isDigit(inputString.charAt(i))){
     return true;
     }else{
       return false;
      }
    }
 }

/*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX. This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()>0) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
    stringComplete = true;
    } 
  }
}
