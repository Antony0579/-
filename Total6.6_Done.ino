#include <IRremote.h>

#define IR_L   A2  //TCRT5000紅外線尋跡(左)
#define IR_R   A3  //TCRT5000紅外線尋跡(右)
#define IR_M   A4  //TCRT5000紅外線尋跡(中)

#define D3   A8  
#define D4   A9  
#define D6   A10  

#define MR1    4   //右馬達輸入
#define ML1    6  //左馬達輸入

#define PHR    12  //右推桿輸入
#define PHL    13  //左推桿輸入
//==================30414258






int S2,S3,S4;
int A,B; //右、左馬達參數

const int In1 = 8;    //左
const int In2 = 7;    
const int In3 = 10;    //右 
const int In4 = 11; 

const int Pin1 = 22;
const int Pin2 = 24;
const int Pin3 = 26;      
const int Pin4 = 28;

int trigPin_r = 3;     //Trig Pin
int echoPin_r = 2;     //Echo Pin
int trigPin_l = 50;                 
int echoPin_l = 48;

int RELAYpin = 30;

long Mode_l = 0;    //模式開關值
long Mode_2 = 0;
long Mode_3 = 0;
long K = 1;     //次數*/



long duration_l, duration_r, duration_m;
long cm_l, cm_r, cm_m;


long Speed = 0;
long speed1 = 0; //右側
long speed2 = 0; //左側  
long slow1 = 0;  //右側
long slow2 = 0;  //左側
long STOP = 0; 

IRsend irsend;
//設定紅外線接收頭的PIN腳


//接收訊號後會把結果存在results
decode_results results;
    
void setup(){
  
Serial.begin(9600);

    pinMode(D3, INPUT);
    pinMode(D4, INPUT);
    pinMode(D6, INPUT);
    
    pinMode(A2,INPUT);
    pinMode(A3,INPUT);
    pinMode(A4,INPUT);

  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT); 
  
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
  pinMode(Pin4, OUTPUT); 

  pinMode(trigPin_l, OUTPUT);        //Define inputs and outputs 
  pinMode(echoPin_l, INPUT);
  pinMode(trigPin_r, OUTPUT);        //Define inputs and outputs 
  pinMode(echoPin_r, INPUT);
    
  pinMode(RELAYpin, OUTPUT);
}

void loop(void) {
      WIFI();
      Ultrasound_left();  
      Ultrasound_right();
      IRtrack();
      Motor(); 
}


void IRtrack()
{

    S2=analogRead(IR_L);
    S3=analogRead(IR_R);
    S4=analogRead(IR_M);
  
    Serial.print("IR_L:");
    Serial.println(S2);
    Serial.println("");
    Serial.print("IR_M:");
    Serial.println(S4);
    Serial.println("");
    Serial.print("IR_R:");
    Serial.println(S3);
    
     delay(50);
}

void Ultrasound_left()
{
  
  digitalWrite(trigPin_l, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin_l, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(trigPin_l, LOW);

 
  pinMode(echoPin_l, INPUT);             // 讀取 echo 的電位
  duration_l = pulseIn(echoPin_l, HIGH);   // 收到高電位時的時間
  cm_l = (duration_l/2) / 29.1;
 
  Serial.print("Distance 左: ");  
  Serial.print(cm_l);
  Serial.print("cm");
  Serial.println();
  delay(100);
   
}

void Ultrasound_right()
{
  digitalWrite(trigPin_r, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin_r, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(trigPin_r, LOW);

 
  pinMode(echoPin_r, INPUT);             // 讀取 echo 的電位
  duration_r = pulseIn(echoPin_r, HIGH);   // 收到高電位時的時間
  cm_r = (duration_r /2) / 29.1;
 
  Serial.print("Distance 右 : ");  
  Serial.print(cm_r);
  Serial.print("cm");
  Serial.println();
  delay(100);

}

void SPD_fr(long sr,long sl){
  
        digitalWrite(In1, HIGH);
        digitalWrite(In2, LOW);
        digitalWrite(In3, HIGH);
        digitalWrite(In4, LOW);
        analogWrite(MR1,sr);
        analogWrite(ML1,sl);
        
        Serial.print("R_SPEED1 : "); 
        Serial.print(sr);
        Serial.print("\n");  
        delay(50);
        Serial.print("R_SPEED2 : "); 
        Serial.print(sl);
        Serial.print("\n");  
        delay(50);
      }
void SPD_fl(long sr,long sl){
  
        digitalWrite(In1, HIGH);
        digitalWrite(In2, LOW);
        digitalWrite(In3, HIGH);
        digitalWrite(In4, LOW);
        analogWrite(MR1,sr);
        analogWrite(ML1,sl);
                   
        Serial.print("R_SPEED1 : "); 
        Serial.print(sr);
        Serial.print("\n");  
        delay(50);
        Serial.print("R_SPEED2 : "); 
        Serial.print(sl);
        Serial.print("\n");  
        delay(50);
      }


void PUSH(){
        digitalWrite(Pin1, HIGH);
        digitalWrite(Pin2, LOW);
        digitalWrite(Pin3, HIGH);
        digitalWrite(Pin4, LOW);
        analogWrite(PHR,220);
        analogWrite(PHL,255);
        delay(30000);   
        
        digitalWrite(Pin1, LOW);
        digitalWrite(Pin2, HIGH); 
        digitalWrite(Pin3, LOW);
        digitalWrite(Pin4, HIGH);
        analogWrite(PHR,235);
        analogWrite(PHL,255);
        delay(30000); 
         
        Serial.print("SPEED_PH : 255"); 
        Serial.print("\n");  
        delay(100);
                
  }


/*void BACK180(){  
  if (Mode_l == 100){
        digitalWrite(In1, HIGH);
        digitalWrite(In2, LOW);
        digitalWrite(In3, LOW);
        digitalWrite(In4, HIGH);  
        analogWrite(MR1,120);
        analogWrite(ML1,140);
        delay(4500);}
        
   if (Mode_2 == 200){
        digitalWrite(In1, HIGH);
        digitalWrite(In2, LOW);
        digitalWrite(In3, LOW);
        digitalWrite(In4, HIGH);  
        analogWrite(MR1,120);
        analogWrite(ML1,140);
        delay(4500);}
        
   if (Mode_3 == 300){
        digitalWrite(In1, HIGH);
        digitalWrite(In2, LOW);
        digitalWrite(In3, LOW);
        digitalWrite(In4, HIGH);  
        analogWrite(MR1,120);
        analogWrite(ML1,140);
        delay(4500);}
  }*/




void Motor(){
 
     if (cm_l < 0 || cm_r < 0)
       { Speed = 0;
          Serial.println(Speed);
           SPD_fl(STOP, STOP);
             Serial.print("停止 ");
             Serial.print("\n");
          
       } 
     else  
       {  Speed = 1;
           Serial.println(Speed);
           A = 90;   //右
           speed1 = Speed*A;
           slow1 = speed1*0.7;
           B = 115;    //左
           speed2 = Speed*B;
           slow2 = speed2*0.7;
           int IR2=400;       //紅外線臨界值650
           int IR4=350;
           int IR3=600;
         if(S2<IR2 && S4>IR4 && S3<IR3 )        //紅黑紅  //LMR
           {  
              digitalWrite(In1, HIGH);
              digitalWrite(In2, LOW);
              digitalWrite(In3, HIGH);
              digitalWrite(In4, LOW);
              analogWrite(MR1,speed1);
              analogWrite(ML1,speed2);
                         
              Serial.print("R_SPEED1 : "); 
              Serial.print(speed1);
              Serial.print("\n");  
              delay(50);
              Serial.print("R_SPEED2 : "); 
              Serial.print(speed2);
              Serial.print("\n");  
              delay(50);    
             Serial.print("前進 ");
             Serial.print("\n");
             }    
             
         else if(S2>IR2 && S4>IR4 && S3<IR3 )   //黑黑紅    
         {
             SPD_fl(speed1, slow2);
             Serial.print("左轉 ");
             Serial.print("\n");
          }
        else if(S2>IR2 && S4<IR4 && S3<IR3 )    //黑紅紅   
         { 
            SPD_fl(speed1, slow2);
             Serial.print("左轉 ");
             Serial.print("\n");
          }
         else if(S2>IR2 && S4>IR4 && S3>IR3 )   //黑黑黑    
         { 
             
             Serial.print("*************************************");
             Serial.print("\n"); 
             Choice();           
          }    
          else if(S2>IR2 && S4<IR4 && S3>IR3 )  //黑紅黑   
         { /*
               digitalWrite(In1, LOW);             
               digitalWrite(In2, HIGH);            
               digitalWrite(In3, LOW);             
               digitalWrite(In4, HIGH);
              
               analogWrite(MR1,slow1);
               analogWrite(ML1,slow2);
              
               Serial.print("倒退 ");
               Serial.print("\n");


               Serial.print("BACK1 : "); 
               Serial.print(slow1);
               Serial.print("\n");  
               delay(50);
               Serial.print("BACK2 : "); 
               Serial.print(slow2);
               Serial.print("\n");  
               delay(50);    */
          }    
          else if(S2<IR2 && S4>IR4 && S3>IR3 )  //紅黑黑    
         { 
            SPD_fr(slow1, speed2);
             Serial.print("右轉 ");
             Serial.print("\n");      
          }    
          else if(S2<IR2 && S4<IR4 && S3>IR3 )  //紅紅黑    
        { 
            SPD_fr(slow1, speed2);
             Serial.print("右轉 ");
             Serial.print("\n");       
         }  
          else if(S2<IR2 && S4<IR4 && S3<IR3 )  //紅紅紅   //LMR
           {
               digitalWrite(In1, LOW);            
               digitalWrite(In2, HIGH);           
               digitalWrite(In3, LOW);             
               digitalWrite(In4, HIGH);

               slow1 = speed1*0.8;
               slow2 = speed2*0.8;
               
               analogWrite(MR1,slow1);
               analogWrite(ML1,slow2);
               Serial.print("倒退 ");
               Serial.print("\n");


               Serial.print("BACK1 : "); 
               Serial.print(slow1);
               Serial.print("\n");  
               delay(50);
               Serial.print("BACK2 : "); 
               Serial.print(slow2);
               Serial.print("\n");  
               delay(50); 
               }            

           }      
       }
       
/*void IRread() {
  //繼電器訊號位 30
  
  if (irrecv.decode(&results)) {
    Serial.println();
    Serial.println(results.value, HEX); //接收訊號，以*進位型式輸出到監控視窗
    delay(500); 
    
  if(results.value == 0xFF6897){
    Serial.println("Emergency STOP");
      digitalWrite(RELAYpin, LOW);
      K = 1;
      } 

  if(results.value == 0xFF30CF){  //A-1
      Mode_l = 100;
      Serial.println("Mode_l");
      digitalWrite(RELAYpin, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(38, LOW);
      digitalWrite(40, LOW);
    }
  else if(results.value == 0xFF18E7){  //B-2
      Mode_2 = 200;
      Serial.println("Mode_2");
      digitalWrite(RELAYpin, HIGH);
      digitalWrite(D3, LOW);
      digitalWrite(38, HIGH);
      digitalWrite(40, LOW);
    }
  else if(results.value == 0xFF7A85){  //C-3
      Mode_3 = 300;
      Serial.println("Mode_3");
      digitalWrite(RELAYpin, HIGH);
      digitalWrite(D3, LOW);
      digitalWrite(38, LOW);
      digitalWrite(40, HIGH);
    }
    
    irrecv.resume(); // 接著接收下一個訊號
  }
  delay(100);
}*/


//IRread ==> ESP8266
void WIFI() {
  //繼電器訊號位 30 (關閉)
  Serial.println(analogRead(D3));
  Serial.println(analogRead(D4));
  Serial.println(analogRead(D6));
  Serial.println("");
  delay(100); 

  int Adc = 400;
  
  
  if(analogRead(D3)< Adc && analogRead(D4)< Adc && analogRead(D6)< Adc){
    Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~STOP");
      digitalWrite(RELAYpin, LOW);
      K = 1;
      Mode_l = 0;
      Mode_2 = 0;
      Mode_3 = 0;
      } 
  else if (analogRead(D3)> Adc && analogRead(D4)< Adc && analogRead(D6)< Adc){    //100 = A
      digitalWrite(RELAYpin,HIGH);
      Mode_l = 100;
      Mode_2 = 0;
      Mode_3 = 0;
      Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~Mode_l");
      }
  else if (analogRead(D3)> Adc && analogRead(D4)> Adc && analogRead(D6)< Adc){    //110 = B
      digitalWrite(RELAYpin,HIGH);
      Mode_l = 0;
      Mode_2 = 200;
      Mode_3 = 0;
      Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~Mode_2");
      }    
  else if (analogRead(D3)< Adc && analogRead(D4)> Adc && analogRead(D6)< Adc){    //010 = B
      digitalWrite(RELAYpin,HIGH);
      Mode_l = 0;
      Mode_2 = 200;
      Mode_3 = 0;
      Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~Mode_2");
      }
  else if (analogRead(D3)< Adc && analogRead(D4)< Adc && analogRead(D6)> Adc){    //001 = C
      digitalWrite(RELAYpin,HIGH);
      Mode_l = 0;
      Mode_2 = 0;
      Mode_3 = 300;
      Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~Mode_3");
      }
  else if (analogRead(D3)> Adc && analogRead(D4)< Adc && analogRead(D6)> Adc){    //101 = C
      digitalWrite(RELAYpin,HIGH);
      Mode_l = 0;
      Mode_2 = 0;
      Mode_3 = 300;
      Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~Mode_3");
      } 
  else if (analogRead(D3)< Adc && analogRead(D4)> Adc && analogRead(D6)> Adc){    //011  = C
      digitalWrite(RELAYpin,HIGH);
      Mode_l = 0;
      Mode_2 = 0;
      Mode_3 = 300;
      Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~Mode_3");
      }
  else if (analogRead(D3)> Adc && analogRead(D4)> Adc && analogRead(D6)> Adc){    //111  = C
      digitalWrite(RELAYpin,HIGH);
      Mode_l = 0;
      Mode_2 = 0;
      Mode_3 = 300;
      Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~Mode_3_A");
      }
  delay(100);
}



void SPD_C(long scr,long scl){
  
        digitalWrite(In1, HIGH);
        digitalWrite(In2, LOW);
        digitalWrite(In3, HIGH);
        digitalWrite(In4, LOW);
        analogWrite(MR1,scr);
        analogWrite(ML1,scl);
        delay(1000);
        
        digitalWrite(In1, LOW);
        digitalWrite(In2, LOW);
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
           
        Serial.print("SPEED1 : "); 
        Serial.print(scr);
        Serial.print("\n");  
        delay(50);
        Serial.print("SPEED2 : "); 
        Serial.print(scl);
        Serial.print("\n");  
        delay(50);
      }


void Choice() //白
{
     /*long scr_a = 120;
     long scl_b = 70;
     long scr_b = 90;
     long scl_a = 140;*/
     long sc_v = 90;
     long sc_t = 0;
     // K = 1
       if (Mode_l == 100)//A 
          { 
            switch(K) {
               
                case 1:
                K = 1;
                Serial.println("K = 1");
                    SPD_C(sc_t, sc_t);                    
                    Serial.print("停止 ");
                    Serial.print("\n");  
                    delay(2000);
                    PUSH();

                    for (int i = 0; i < 50; i++) {
                    irsend.sendNEC(0xFF30CF, 32); //10EFA05F(小編家的電視開關編碼)
                    Serial.println("0xFF30CF");
                    delay(40);
                    }
                    
                    SPD_C(sc_v, sc_v);
                    Serial.print("前進 ");
                    Serial.print("\n");
                    K += 1 ;
                break;

                case 2:
                Serial.println("K = 2");
                    SPD_C(sc_v, sc_v);
                    Serial.print("前進 ");
                    Serial.print("\n");
                    K += 1 ;
                break;

                case 3:
                Serial.println("K = 3");
                    SPD_C(sc_v, sc_v);
                    Serial.print("前進 ");
                    Serial.print("\n");
                    K += 1 ;
                break;
                
                case 4:
                Serial.println("K = 4, END");
                    SPD_C(sc_v, sc_v);
                    Serial.print("前進 ");
                    Serial.print("\n");
                    delay(500);
                    
                    SPD_C(sc_t, sc_t);
                    Serial.print("程式終止 ");
                    Serial.print("\n");
                    digitalWrite(RELAYpin, LOW);
                    K = 0 ;
                break;

               }
           } 
      else if (Mode_2 == 200) //B    
           { 
            switch(K) {
                case 1:
                K = 1;
                Serial.println("K = 1");
                    SPD_C(sc_v, sc_v);
                    Serial.print("前進 ");
                    Serial.print("\n");
                    K += 1 ;
                break;

                case 2:
                Serial.println("K = 2");
                    SPD_C(sc_t, sc_t);                    
                    Serial.print("停止 ");
                    Serial.print("\n");  
                    delay(2000);
                    PUSH();
                    
                    for (int i = 0; i < 50; i++) {
                    irsend.sendNEC(0xFF18E7, 32); //10EFA05F(小編家的電視開關編碼)
                    Serial.println("0xFF18E7");
                    delay(40);
                    }

                    SPD_C(sc_v, sc_v);
                    Serial.print("前進 ");
                    Serial.print("\n");
                    K += 1 ;
                break;

                case 3:
                Serial.println("K = 3");
                    SPD_C(sc_v, sc_v);
                    Serial.print("前進 ");
                    Serial.print("\n");
                    K += 1 ;
                break;
                
                case 4:
                Serial.println("K = 4, END");
                    SPD_C(sc_v, sc_v);
                    Serial.print("前進 ");
                    Serial.print("\n");
                    delay(500);
                    
                    SPD_C(sc_t, sc_t);
                    Serial.print("程式終止 ");
                    Serial.print("\n");
                    digitalWrite(RELAYpin, LOW);
                    K = 0 ;
                break;
               }
            }
      else if (Mode_3 == 300)  //C
        { 
           switch(K) {
                case 1:
                K = 1;
                Serial.println("K = 1");
                    SPD_C(sc_v, sc_v);
                    Serial.print("前進 ");
                    Serial.print("\n");
                    K += 1 ;
                break;

                case 2:
                Serial.println("K = 2");
                    SPD_C(sc_v, sc_v);
                    Serial.print("前進 ");
                    Serial.print("\n");
                    K += 1 ;
                break;

                case 3:
                Serial.println("K = 3");
                    SPD_C(sc_t, sc_t);                    
                    Serial.print("停止 ");
                    Serial.print("\n");  
                    delay(2000);
                     PUSH();
                    
                    for (int i = 0; i < 50; i++) {
                    irsend.sendNEC(0xFF7A85, 32); //10EFA05F(小編家的電視開關編碼)
                    Serial.println("0xFF7A85");
                    delay(40);
                    }
                    
                    SPD_C(sc_v, sc_v);
                    Serial.print("前進 ");
                    Serial.print("\n");
                    K += 1 ;
                break;
                
                case 4:
                Serial.println("K = 4, END");
                    SPD_C(sc_v, sc_v);
                    Serial.print("前進 ");
                    Serial.print("\n");
                    delay(500);
                    
                    SPD_C(sc_t, sc_t);
                    Serial.print("程式終止 ");
                    Serial.print("\n");
                    digitalWrite(RELAYpin, LOW);
                    K = 0 ;
                break;
               }
            }
         }
       
