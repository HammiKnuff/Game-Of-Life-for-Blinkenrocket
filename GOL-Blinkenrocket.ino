const int rows[8] = {8, 9, 10, 11, 12, 13, 14, 15};
const int cols[8] = {0, 1, 2, 3, 4, 5, 6, 7};
const int BUTTON = 1;
const int numPatterns = 10;


  
int pixels[8][8];

int x = 0;
int y = 0;

int lifeMap[8][8];

void setup() {

  randomSeed(analogRead(0));
  // put your setup code here, to run once:
  for(int thisPin = 0; thisPin < 8; thisPin++){
        pinMode(rows[thisPin], OUTPUT);
        pinMode(cols[thisPin], OUTPUT);

        digitalWrite(cols[thisPin], HIGH);
        digitalWrite(cols[thisPin], LOW);
      
      }

      pinMode(BUTTON, INPUT);

      Serial.begin(9600);

      randomLifeStart();
      
}

void loop() {
  int i;
  //Serial.println(analogRead(BUTTON));
  for (i = 0; i < 100; i++) {
    refreshLife();
      refreshPixelArray();
      displayPixelArray();
  }
  randomLifeStart();
 // Serial.println(1);
}

void refreshLife(){
    transform(lifeMap);
}

void transform (int oldMap[8][8]){

  int newLife[8][8];
  for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
          newLife[i][j] = flip(oldMap, i , j);
        }
    }

    int countDead;
    int countSame;
    for (int a = 0; a < 8; a++){
        for(int b = 0; b < 8; b++){
            if(lifeMap[a][b] == newLife[a][b]){
                countSame = countSame+1;
              }
            lifeMap[a][b]= newLife[a][b] ;
            if (newLife[a][b] == LOW){
                countDead = countDead+1;
              }
          }
      }

    if(countDead == 64 || countSame == 64){
        randomLifeStart();
      }
   // memcpy(lifeMap, newLife, sizeOf lifeMap);
  //lifeMap = newLife;  
 }

int flip (int oldMap[8][8], int i, int j){
    int count = around(oldMap, i , j);
    //Serial.print(count);

    if(oldMap[i][j] == 1){
        if(count < 2 || count > 3){
            return 0;
          }

          return 1;
      } else {
            if(count == 3){
                return 1;
              }

              return 0;
        } 
  } 

int around (int oldMap[8][8], int i, int j){
      int count = 0;
      for (int a = i-1; a <= i+1; a++){
          for (int b = j-1; b <= j+1; b++){
              if(a==i && b==j){
                  continue;
                }
                count+= eval(oldMap, a, b);
            }
        }
        return count;
  }

  int eval(int oldMap[8][8], int i, int j){
      if(i<0||j<0||i==7||j==7){
          return 0;
        }
      if(oldMap[i][j]==1){
          return 1;
        }

        return 0;
      
    }

void randomLifeStart(){
    for (int i = 0; i < 8; i++){
          for(int j = 0; j < 8; j++){
              long rand = random(0,100);
              Serial.println("random: ");
              Serial.print(rand);
              int binary = 0;
              if(rand > 50) {
                  binary = 1;
                }
              lifeMap[i][j] = binary;
            }
        }
  }

void displayPixelArray() {

  //ON NEEDS ROW HIGH COL LOW
  //PIXELS 1 = ON PIXEL   0 = OFF Pixel
  for(int repeat = 0; repeat < 500; repeat++){
    for (int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            //check if pixel should be on or off
            if(pixels[row][col] == 1) {
              //flash the pixel quickly
              digitalWrite(rows[row], HIGH);
              digitalWrite(cols[col], LOW);

              delayMicroseconds(10);

              digitalWrite(rows[row], LOW);
              digitalWrite(cols[col], HIGH);
          }

          //clear the screen
          digitalWrite(rows[row], LOW);
          digitalWrite(cols[col], HIGH);
      }
  }
  }
}


void refreshPixelArray() {
    //reset everything
    for(int r=0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            pixels[r][c] = 0;
          }
      }

    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            pixels[r][c] = lifeMap[r][c];
          }
      }
}
