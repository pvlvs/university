#include <assert.h>
#include <iostream>
#include <unordered_map>

namespace app {

class Vehicle {
  int wheels;
  double maxSpeed;
  double speed;
  double position;

public:
  Vehicle(const int &wheels, const double &maxSpeed, const float &speed,
          const double &position)
      : position(position) {
    setWheels(wheels);
    setMaxSpeed(maxSpeed);
    setSpeed(speed);
  }

  const void setWheels(const int &wheels) {
    if (wheels < 0) {
      this->wheels = 0;
      return;
    }

    this->wheels = wheels;
  }
  const int getWheels() const { return wheels; }

  const void setMaxSpeed(const double &maxSpeed) {
    if (maxSpeed < 0) {
      this->maxSpeed = 0;
      return;
    }

    this->maxSpeed = maxSpeed;
  }
  const double getMaxSpeed() const { return maxSpeed; }

  const void setSpeed(const double &speed) {
    if (speed > maxSpeed) {
      this->speed = maxSpeed;
      return;
    }
    if (speed < 0) {
      this->speed = 0;
      return;
    }

    this->speed = speed;
  }
  const double getCurrentSpeed() const { return speed; }

  const void setPosition(const double &position) { this->position = position; }
  const double getPosition() const { return position; }

  const void move(const double &minutes) {
    setPosition(position + speed / 60 * minutes);
  }
};

class Car : public Vehicle {
public:
  Car(const double &maxSpeed, const float &speed, const float &position)
      : Vehicle(4, maxSpeed, speed, position) {}
};

class Bicycle : public Vehicle {
public:
  Bicycle(const double &maxSpeed, const float &speed, const float &position)
      : Vehicle(2, maxSpeed, speed, position) {}
};

class PassengerCar : public Car {
public:
  PassengerCar(const double &speed, const float &position)
      : Car(140, speed, position) {}
};

class RacingCar : public Car {
public:
  RacingCar(const double &speed, const float &position)
      : Car(200, speed, position) {}
};

class Ambulance : public PassengerCar {
  bool light = false;

public:
  Ambulance() : Ambulance(0, 0) {}
  Ambulance(const double &speed, const float &position)
      : PassengerCar(speed, position) {}

  const bool isBlueLightOn() const { return light; }
  const void switchBlueLight() { light = !light; }
};

void testVehicle(Vehicle &vehicle, const int &wheels, const double &speed,
                 const double &maxSpeed) {
  assert(vehicle.getWheels() == wheels);
  assert(vehicle.getMaxSpeed() == maxSpeed);
  assert(vehicle.getCurrentSpeed() == 0);
  assert(vehicle.getPosition() == 0);
  vehicle.setSpeed(speed);
  assert(vehicle.getCurrentSpeed() == speed);
  vehicle.move(60);
  vehicle.move(60);
  vehicle.move(60);
  assert(vehicle.getPosition() == speed * 3);
  vehicle.setSpeed(maxSpeed + 100);
  assert(vehicle.getCurrentSpeed() == vehicle.getMaxSpeed());
  vehicle.setSpeed(-10);
  assert(vehicle.getCurrentSpeed() == 0);
  vehicle.setMaxSpeed(-10);
  assert(vehicle.getMaxSpeed() == 0);
}

void testBycicle() {
  Bicycle bycicle(80, 0, 0);

  testVehicle(bycicle, 2, 40, 80);
}

void testPassengerCar() {
  PassengerCar car(0, 0);

  testVehicle(car, 4, 100, 140);
}

void testRacingCar() {
  RacingCar car(0, 0);

  testVehicle(car, 4, 160, 200);
}

void testAmbulance() {
  Ambulance ambulance;
  assert(ambulance.getWheels() == 4);
  assert(ambulance.getMaxSpeed() == 140);
  assert(ambulance.getCurrentSpeed() == 0);
  assert(ambulance.getPosition() == 0);
  ambulance.setSpeed(100);
  assert(ambulance.getCurrentSpeed() == 100);
  ambulance.move(60);
  ambulance.move(60);
  assert(ambulance.getPosition() == 200);
  ambulance.setSpeed(200);
  assert(ambulance.getCurrentSpeed() == ambulance.getMaxSpeed());
  assert(!ambulance.isBlueLightOn());
  ambulance.switchBlueLight();
  assert(ambulance.isBlueLightOn());
}

void race() {
  std::unordered_map<std::string, Vehicle *> map;
  int minutes = 60;

  map["Bicycle"] = new Bicycle(20, 20, 0);
  map["PassengerCar"] = new PassengerCar(150, 0);
  map["RacingCar"] = new RacingCar(200, 0);
  map["Ambulance"] = new Ambulance(80, 0);

  for (int i = 0; i < 5; i++) {
    map["Bicycle"]->move(minutes);

    if (i == 4) {
      map["PassengerCar"]->move(minutes);
      map["RacingCar"]->move(minutes);
      map["Ambulance"]->move(minutes);
    }
  }

  std::cout << "position of ambulance: " << map["Ambulance"]->getPosition()
            << std::endl;
  std::cout << "position of bicycle: " << map["Bicycle"]->getPosition()
            << std::endl;
  std::cout << "position of passenger car: "
            << map["PassengerCar"]->getPosition() << std::endl;
  std::cout << "position of racing car: " << map["RacingCar"]->getPosition()
            << std::endl;
}

} // namespace app

int main() {
  std::cout << "Hi!" << std::endl;

  app::testBycicle();
  app::testPassengerCar();
  app::testRacingCar();
  app::testAmbulance();

  app::race();

  std::cout << "Bye." << std::endl;

  return 0;
}
