#include <FastLED.h>
#include <math.h>
#define NUM_LEDS 96
#define DATA_PIN 6
#define CHUNK_SIZE 20
#define MAX_CHUNKS 10
#define TOTAL_SIZE (CHUNK_SIZE * MAX_CHUNKS)
CRGB leds[NUM_LEDS];
int count = 0;
bool ledStates[NUM_LEDS] = {false}; 
unsigned long previousMillis = 0;  // Stores the last time the LED was updated
unsigned long interval = 500;         // Interval at which to blink (milliseconds)
char dataBuffer[TOTAL_SIZE + 1];  // Buffer to store the concatenated chunks, +1 for null terminator
int dataBufferIndex = 0;  // Index for the data buffer



const byte numChars = 800;
char receivedChars[numChars];

boolean newData = false;

void extractCharsExceptComma(char* input, char* output) {
  int j = 0;  // Index for the output array
  for (int i = 0; input[i] != '\0'; i++) {  // Iterate through the input array until the null terminator
    if (input[i] != ',') {  // Check if the character is not a comma
      output[j++] = input[i];  // Copy the character to the output array and increment the index
    }
  }
  output[j] = '\0';  // Null-terminate the output array
}

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    Serial.println("<Arduino is ready>");
    
}


void loop() {
  static char buffer[41];  // Adjust the size based on chunk_size + 1 for null terminator
  static int index = 0;

  while (Serial.available() > 0) {
    char receivedChar = Serial.read();
    buffer[index++] = receivedChar;

    // Check if chunk is complete or if it's the end of the message
    if (index >= 20 || receivedChar == '\n' || receivedChar == '>') {
      buffer[index] = '\0';  // Null-terminate the string
      Serial.print("Received chunk: ");
      Serial.println(buffer);

      char output[sizeof(buffer)];  // Create an output array of the same size as the input
      extractCharsExceptComma(buffer, output);
      Serial.println(output);

      strcat (dataBuffer, output);

      // Send confirmation back to Python
      Serial.println("ACK");

      // Reset buffer and index for the next chunk
      memset(buffer, 0, sizeof(buffer));
      index = 0;
    }
  }
  // if (strlen(dataBuffer) == 98){
  //   Serial.println("it works!");
  //   processChunk(dataBuffer);
  //   memset(dataBuffer, '\0', sizeof(dataBuffer));
  // }
  



}


void processChunk(char* chunk1) {
  // Add your code to process the chunk, e.g., parse LED indices and set colors
  Serial.println("ProcessChunk activated");

  for (int i = 1; i<97; i++){
    if (chunk1[i] == '1'){
      leds[i-1] = CRGB::Red;
      
    }else{
      leds[i-1] = CRGB::Black;

    }
  }
  FastLED.show();
  

}





//// Trash

// Example 3 - Receive with start- and end-markers
// #include <FastLED.h>
// #include <math.h>
// #define NUM_LEDS 96
// #define DATA_PIN 2
// CRGB leds[NUM_LEDS];
// bool ledStates[NUM_LEDS] = {false}; 
// unsigned long previousMillis = 0;  // Stores the last time the LED was updated
// unsigned long interval = 500;         // Interval at which to blink (milliseconds)



// const byte numChars = 800;
// char receivedChars[numChars];

// boolean newData = false;

// void setup() {
//     Serial.begin(9600);
//     FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
//     Serial.println("<Arduino is ready>");
// }


// void loop() {
//   static char buffer[21];  // Adjust the size based on chunk_size + 1 for null terminator
//   static int index = 0;

//   while (Serial.available() > 0) {
//     char receivedChar = Serial.read();
//     buffer[index++] = receivedChar;

//     if (index >= 20 || receivedChar == '\n') {  // Chunk complete or end of message
//       buffer[index] = '\0';  // Null-terminate the string
//       Serial.print("Received chunk: ");
//       Serial.println(buffer);

//       // Process the chunk
//       // (Your code to process the chunk)

//       // Send confirmation back to Python
//       Serial.println("ACK");

//       // Reset buffer and index for the next chunk
//       memset(buffer, 0, sizeof(buffer));
//       index = 0;
//     }
//   }
// }

// // void loop() {
  

// //     recvWithStartEndMarkers();
// //     if (newData == true) {
// //         Serial.print("Received: ");
// //         Serial.println(receivedChars);
// //         // Process the received data here
// //         newData = false; // Reset the newData flag after processing
// //     }
// //     // delay(500);
// //     // showNewData();

// // }

// void recvWithStartEndMarkers() {
//     static boolean recvInProgress = false;
//     static byte ndx = 0;
//     char startMarker = '<';
//     char endMarker = '>';
//     char rc;
 
//     while (Serial.available() > 0 && newData == false) {

//       rc = Serial.read();

//       if (recvInProgress == true) {
//           if (rc != endMarker) {
//               receivedChars[ndx] = rc;
//               ndx++;
//               if (ndx >= numChars) {
//                   ndx = numChars - 1;
//               }
//           }
//           else {
//               receivedChars[ndx] = '\0'; // terminate the string
//               recvInProgress = false;
//               ndx = 0;
//               newData = true;
              
//           }
//       }

//       else if (rc == startMarker) {
//           recvInProgress = true;
//         }

      
//     }
//     clearSerialBuffer();
// }

// void showNewData() {
//   Serial.println("show new data called");
//   if (newData == true) {
//     Serial.println("New data recieved.");
//     char *token = strtok(receivedChars, ",");
    
//     while(token != NULL){
//       Serial.print(token);
//       // if (*token == 'x'){
//         // Serial.print(token);
//         // int ledIndex = atoi(token + 1);
//         // leds[ledIndex] = CRGB::Black;
//       // } else{
//       //   int ledIndex = atoi(token);
//       //   leds[ledIndex] = CRGB::Red;

//       // }
//       token = strtok(NULL, ",");

//     }
//   }
// }


// void clearSerialBuffer() {
//     while (Serial.available() > 0) {
//         Serial.read();
//     }
// }



// void showNewData() {
//   // if (newData) {
//   //   Serial.print("This just in ... ");
//   //   Serial.println(receivedChars);

//   //   char *token = strtok(receivedChars, ",");
//   //   while (token != NULL) {
//   //       Serial.println(token);
//   //       if (*token == 'x') {
//   //           // Parse the well number after 'x'
//   //           int wn = atoi(token + 1);  // token + 1 skips the 'x' character
//   //           if (wn >= 0 && wn < NUM_LEDS) {
//   //               leds[wn] = CRGB::Black;  // Turn off the corresponding LED
//   //           } else {
//   //               Serial.println("Invalid LED index");
//   //           }
//   //       } else {
//   //           int wn = atoi(token);
//   //           if (wn >= 0 && wn < NUM_LEDS) {
//   //               leds[wn] = CRGB::Red;  // Turn on the LED for a valid well number
//   //           } else {
//   //               Serial.println("Invalid LED index");
//   //           }
//   //       }
//   //       token = strtok(NULL, ",");
//   //   }

//   //   newData = false;
//   //   FastLED.show();
//   //   memset(receivedChars, '\0', numChars);
//   //   }
//   if (newData == true) {
//       // Serial.print("This just in ... ");
//       // Serial.println(receivedChars);
//       char *token1 = strtok(receivedChars, ",");
//       // Serial.println(*token1 == 'x');
//       // if (*token1 == 'x'){
//       //   leds[0] = CRGB::Black;
//       // }
//       // else{
//       //   int wn = atoi(token1);
//       //   leds[wn] = CRGB::Red;
//       // }
//       // // Serial.println(token1);
//       // char *token = strtok(NULL, ",");
//       while(token1 != NULL){
//         // Serial.println(token);
//         if (*token1 == 'x'){
//           Serial.println("off");
//           // int wn1 = atoi(token);
//           // leds[wn1] = CRGB::Black;
//         }
//         else{
//           Serial.println("on");
//           // int wn1 = atoi(token);
//           // leds[wn1] = CRGB::Red;
//         }
//         token1 = strtok(NULL, ",");
//       }

//       newData = false;
//       FastLED.show();
//       // Clear receivedChars using memset
//       memset(receivedChars, '\0', numChars);

        
//     }
// }

 
  
  // if (newData == true) {
  //     char *token = strtok(receivedChars, ",");
      
  //     while(token != NULL){
  //       if (*token == 'x'){
  //         Serial.print(token);
  //         int ledIndex = atoi(token + 1);
  //         leds[ledIndex] = CRGB::Black;
  //       } else{
  //         int ledIndex = atoi(token);
  //         leds[ledIndex] = CRGB::Red;

  //       }
  //       token = strtok(NULL, ",");

        // if (*token1 == 'x'){
        //   Serial.println("off");
        //   leds[1] = CRGB::Black;
        // }
        // else{
        //   Serial.println("on");
        //   leds[1] = CRGB::Red;
        // }
        // token1 = strtok(NULL, ",");
      // }
  

////////////////////// Blinking Fail////////////////////////////////


// void showNewData() {
// // // // Find the last token (frequency value)
// // //   char *lastToken = strrchr(receivedChars, ',');
// // //   if (lastToken != NULL) {
// // //     // Convert the frequency value to an integer and assign it to interval
// // //     long interval = atoi(lastToken + 1);
// // //     // Remove the last token from the string
// // //     *lastToken = '\0';
// // //   }
// //   if (newData) {
// //     char *token = strtok(receivedChars, ",");
// //     while (token != NULL) {
// //     int ledIndex = atoi(token);
// //     if (ledIndex >= 0 && ledIndex < NUM_LEDS) {
// //       ledStates[ledIndex] = !ledStates[ledIndex];  // Toggle the state of the specified LED
// //     }
// //     token = strtok(NULL, ",");
// //   }
// //   newData = false;
// //   memset(receivedChars, '\0', numChars);
// // }
//   // // Find the last comma in the received string
//   //   char *lastComma = strrchr(receivedChars, ',');
//   //   if (lastComma != NULL) {
//   //     // Convert the substring after the last comma to an integer
//   //     interval = strtoul(lastComma + 1, NULL, 10);
//   //     // Replace the last comma with a null terminator to remove the interval from the string
//   //     *lastComma = '\0';
//   //   }
//   if (newData) {
//     // Process the tokens for LED indices
//     char *token = strtok(receivedChars, ",");
//     while (token != NULL) {
//       if (*token == 'x') {
//         int ledIndex = atoi(token + 1);  // Get the index after 'x'
//         if (ledIndex >= 0 && ledIndex < NUM_LEDS) {
//           leds[ledIndex] = CRGB::Black;  // Turn off the specified LED
//           ledStates[ledIndex] = false;   // Update the state to off
//         }
//       } else {
//         int ledIndex = atoi(token);      // Get the index
//         if (ledIndex >= 0 && ledIndex < NUM_LEDS) {
//           ledStates[ledIndex] = true;    // Upda