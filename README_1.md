# Arduino Soil Moisture Monitoring System

An embedded systems project that monitors soil moisture using two metal probes and an Arduino Uno. Provides real-time visual and audible alerts based on soil condition.

---

## How It Works

Two metal probes inserted into soil form a voltage divider with a 10 kΩ resistor. The Arduino reads the voltage at A0 and converts it to a value between 0 and 1023. This value is compared against a threshold to determine if the soil is wet or dry.

| ADC Reading | Condition | Blue LED | Red LED | Buzzer |
|-------------|-----------|----------|---------|--------|
| 0 – 499     | Wet Soil  | ON       | OFF     | OFF    |
| 500 – 1023  | Dry Soil  | OFF      | ON      | ON     |

---

## Features

- Real-time soil moisture reading via `analogRead()` every 500ms
- Blue LED indicates wet soil, red LED indicates dry soil
- Active buzzer alarm when soil is dry
- Live Serial Monitor output at 9600 baud for calibration
- Configurable threshold — one constant to change
- No external libraries required

---

## Hardware

### Components

| Component | Quantity |
|-----------|----------|
| Arduino Uno | 1 |
| Soil Moisture Probes (Metal) | 1 Pair |
| 10 kΩ Resistor | 1 |
| Blue LED | 1 |
| Red LED | 1 |
| 220 Ω Resistors | 2 |
| Active Buzzer | 1 |
| Breadboard | 1 |
| Jumper Wires | Several |

### Pin Connections

| Arduino Pin | Variable | Connected To |
|-------------|----------|--------------|
| A0 | `soilPin` | Voltage divider output |
| D8 | `blueLED` | Blue LED (via 220 Ω) |
| D9 | `redLED` | Red LED (via 220 Ω) |
| D10 | `buzzer` | Active buzzer |
| 5V | — | Voltage divider top rail |
| GND | — | Common ground |

### Wiring Diagram

```
              +5V
               |
            10kΩ
               |
               +-----------> A0
               |
          Soil Probe 1
               |
             (Soil)
               |
          Soil Probe 2
               |
              GND

Blue LED:  D8  ----[220Ω]----|>|---- GND
Red LED:   D9  ----[220Ω]----|>|---- GND
Buzzer:    D10 --------[Buzzer]------ GND
```

---

## Code

```cpp
const int soilPin  = A0;
const int blueLED  = 8;
const int redLED   = 9;
const int buzzer   = 10;

// Adjust this after testing
const int threshold = 500;

void setup() {
  pinMode(blueLED, OUTPUT);
  pinMode(redLED,  OUTPUT);
  pinMode(buzzer,  OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int soilValue = analogRead(soilPin);

  Serial.print("Soil Moisture: ");
  Serial.println(soilValue);

  if (soilValue >= threshold) {
    // Soil is dry
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED,  HIGH);
    digitalWrite(buzzer,  HIGH);
  } else {
    // Soil is wet
    digitalWrite(blueLED, HIGH);
    digitalWrite(redLED,  LOW);
    digitalWrite(buzzer,  LOW);
  }

  delay(500);
}
```

---

## Setup

1. Wire components as shown above
2. Open Arduino IDE
3. Paste the sketch and upload to Arduino Uno
4. Open Serial Monitor — set baud to **9600**
5. Insert probes into soil and observe readings

---

## Calibration

The default threshold of `500` may not suit every soil type.

1. Insert probes into fully **wet** soil — note the ADC value
2. Let the soil dry completely — note the ADC value
3. Set `threshold` to the midpoint of the two values
4. Re-upload and verify the LEDs switch correctly

**Example:** wet reads ~150, dry reads ~820 → threshold of `500` works well.

---

## Serial Output

```
Soil Moisture: 180   → wet (blue LED on)
Soil Moisture: 785   → dry (red LED on, buzzer on)
```

---

## Limitations

- Metal probes corrode over time in moist soil
- Threshold needs calibration per soil type
- No automatic watering — alert only
- No data logging between power cycles
- Serial Monitor requires USB connection

---

## Future Improvements

- Add 16×2 LCD for standalone display
- Integrate relay + water pump for auto irrigation
- Upgrade to ESP32 for Wi-Fi and remote monitoring
- Map ADC to percentage: `moisture% = map(soilValue, 0, 1023, 100, 0)`
- Log data to SD card

---

## License

MIT License — free to use, modify, and distribute.
