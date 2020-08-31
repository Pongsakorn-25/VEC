int Ph  = 6;        //arduino pin connected to the Ph pin of 4543
int BL  = 5;        //arduino pin connected to the BL pin of 4543
int LD  = 11;      //arduino pin connected to the LD pin of 4543


int A   = 7;
int B   = 9;
int C   = 10;
int D   = 8;

void setup()
{     
    // Declare all the pins as OUTPUT pins
  
  pinMode(Ph,  OUTPUT);
  pinMode(BL,  OUTPUT);
  pinMode(LD, OUTPUT);

  pinMode(A , OUTPUT);
  pinMode(B  , OUTPUT);
  pinMode(C  , OUTPUT); 
  pinMode(D, OUTPUT);

}

void loop()
{

    // Display 0

  digitalWrite(Ph,  HIGH); 
  digitalWrite(BL,  LOW);   
  digitalWrite(LD,  HIGH); 

  digitalWrite(A , LOW); 
  digitalWrite(B , LOW);   
  digitalWrite(C , LOW);
  digitalWrite(D , LOW);

  delay(1000);

    // Display 1

  digitalWrite(A , HIGH); 
  digitalWrite(B , LOW);   
  digitalWrite(C , LOW);
  digitalWrite(D , LOW);

  delay(1000);

    // Display 2

  digitalWrite(A , LOW); 
  digitalWrite(B , HIGH);   
  digitalWrite(C , LOW);
  digitalWrite(D , LOW);

  delay(1000);

    // Display 3

  digitalWrite(A , HIGH); 
  digitalWrite(B , HIGH);   
  digitalWrite(C , LOW);
  digitalWrite(D , LOW);

  delay(1000);

    // Display 4

  digitalWrite(A , LOW); 
  digitalWrite(B , LOW);   
  digitalWrite(C , HIGH);
  digitalWrite(D , LOW);

  delay(1000); 
}
