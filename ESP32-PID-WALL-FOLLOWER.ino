#define TRIG_KIRI 13
#define ECHO_KIRI 12
#define TRIG_KANAN 14
#define ECHO_KANAN 27

#define ENA 15
#define ENB 5
#define IN1 2
#define IN2 4
#define IN3 16
#define IN4 17

float Kp = 3.6;
float Ki = 0.0006;
float Kd = 0.28;

float error = 0;
float error_sebelumnya = 0;
float integral = 0;
float turunan = 0;
float kontrol = 0;

float kiri_sebelumnya = 50;
float kanan_sebelumnya = 50;

int kecepatan_dasar = 70;
int pwm_maksimal = 180;
int waktu_sampling = 25;

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_KIRI, OUTPUT);
  pinMode(ECHO_KIRI, INPUT);
  pinMode(TRIG_KANAN, OUTPUT);
  pinMode(ECHO_KANAN, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {

  float kiri = bacaSensor(TRIG_KIRI, ECHO_KIRI);
  float kanan = bacaSensor(TRIG_KANAN, ECHO_KANAN);

  kiri = (kiri * 0.6) + (kiri_sebelumnya * 0.4);
  kanan = (kanan * 0.6) + (kanan_sebelumnya * 0.4);

  kiri_sebelumnya = kiri;
  kanan_sebelumnya = kanan;

  float dt = waktu_sampling / 1000.0;

  float selisih = kanan - kiri;

  error = selisih * (0.7 + abs(selisih) / 80.0);

  integral += error * dt;
  integral = constrain(integral, -8, 8);

  turunan = (error - error_sebelumnya) / dt;

  kontrol = (Kp * error) + (Ki * integral) + (Kd * turunan);

  kontrol = kontrol * (1.0 + abs(kontrol) / 180.0);

  kontrol = kontrol * 0.92;
  kontrol = constrain(kontrol, -130, 130);

  float keseimbangan = abs(error);

  float faktor_kecepatan = 1.0 - (keseimbangan / 60.0);
  faktor_kecepatan = constrain(faktor_kecepatan, 0.55, 1.0);

  int kecepatan = kecepatan_dasar * faktor_kecepatan;

  int motor_kiri = kecepatan + kontrol;
  int motor_kanan = kecepatan - kontrol;

  motor_kiri = constrain(motor_kiri, 0, pwm_maksimal);
  motor_kanan = constrain(motor_kanan, 0, pwm_maksimal);

  gerakMotor(motor_kiri, motor_kanan);

  error_sebelumnya = error;

  delay(waktu_sampling);
}

float bacaSensor(int trig, int echo) {

  float total = 0;

  for (int i = 0; i < 3; i++) {

    digitalWrite(trig, LOW);
    delayMicroseconds(2);

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    long durasi = pulseIn(echo, HIGH, 30000);

    float jarak = durasi * 0.034 / 2;

    jarak = jarak + (jarak == 0) * 50;

    total += jarak;

    delay(5);
  }

  return total / 3.0;
}

void gerakMotor(int kiri, int kanan) {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, kiri);
  analogWrite(ENB, kanan);
}
