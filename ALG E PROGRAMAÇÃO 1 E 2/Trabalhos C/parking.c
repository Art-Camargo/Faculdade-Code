#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct park {
  struct park *nextCar;
  int license, manobra;
}park;

void inParking(park **startCar, int license) {
  park *newCar = (park*)malloc(sizeof(park));
  if (newCar) {
    newCar->manobra = 0;
    newCar->license = license;
    if (*startCar == NULL) {
      *startCar = newCar;
      newCar->nextCar = NULL;
    }
    else {
      newCar->nextCar = *startCar;
      *startCar = newCar;
    }
  }
}

void outParking(park **firstCar, int license, park *currentCar, park *previousCar) {
  park *freeCar;
  if (currentCar != NULL) {
    if (currentCar->license == license) {
      if (previousCar == NULL) {
        *firstCar = currentCar->nextCar;
        freeCar = currentCar;
        currentCar = currentCar->nextCar;
        printf("\no carro: %p, placa: %d saiu do estacionamento", freeCar, freeCar->license);
        free(freeCar);
      }
      else {
        previousCar->nextCar = currentCar->nextCar;
        freeCar = currentCar;
        currentCar = currentCar->nextCar;
        printf("\no carro: %p, placa: %d saiu do estacionamento", freeCar, freeCar->license);
        free(freeCar);
      }
    }
    else {
      outParking(firstCar, license, currentCar->nextCar, currentCar);
    }
  }
}

bool carInParking(park *car, int license) {
  while(car) {
    if (car->license == license) {
      return true;
    }
    car = car->nextCar; 
  }
  return false;
}

void showParking(park *showPark) {
  if (showPark == NULL) {
    printf("\nO estacionamento esta vazio!");
  }
  else {
    while(showPark != NULL) {
      printf("\nplaca: %d, carro: %p, manobras: %d", showPark->license, showPark, showPark->manobra);
      showPark = showPark->nextCar;
    }
  }
}

int CarCounter(park *firstCarPark) {
  int counterCar = 0;
  while(firstCarPark != NULL) {
    counterCar++;
    firstCarPark = firstCarPark->nextCar;
  }
  return counterCar;
}

int dailyControlParking() {
  int option;
  do {
    printf("\n\n1 - entrar carro no estacionamento\n2 - sair carro do estacionamento");
    printf("\n3 - mostrar estacionamento\n4 - fechar estacionamento\n\nEscolha uma opcao acima: ");
    scanf("%d", &option);
  } while(option < 1 || option > 4);
  return option;
}

int receiveLicense() {
  int license;
  do {
    printf("\nInforme a placa (placas de 1 a 999): ");
    scanf("%d", &license);
  }while((license > 999 || license < 1));
  return license;
}

int previousCounter(park *cars, int license) {
  int carCount = 0;
  while(cars != NULL) {
    if (cars->license != license) {
      printf("\no carro: %p placa: %d manobrou", cars, cars->license);
      cars->manobra = cars->manobra + 1;
      carCount++;
    }
    else {
      return carCount;
    }
    cars = cars->nextCar;
  }
  return carCount;
}

int main() {
  park *parking = NULL;
  int option, license, count;
  do {
    option = dailyControlParking();
    system("cls||clear");
    switch (option) {
      case 1:
        if (CarCounter(parking) < 10) {
          do {
            license = receiveLicense();
          } while(carInParking(parking, license));
          inParking(&parking, license);
        }
        else {
          printf("\nO estacionamento esta cheio!");
        }
      break;
      case 2:
        if (parking != NULL) {
          printf("\nInforme qual placa voce quer remover abaixo");
          showParking(parking);
          do {
            license = receiveLicense();
          } while(!carInParking(parking, license));
          system("cls||clear");
          count = previousCounter(parking, license);
          outParking(&parking, license, parking, NULL);
          if (count > 0) {
            printf("\nO carro de placa %d deu %d manobras e saiu do estacionamento", license, count);
          }
        }
      break;
      case 3:
        showParking(parking);
      break;
      case 4:
        printf("\nPortao fechou\n");
      break;
    }
  } while(option != 4);
}