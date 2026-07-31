#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

class Car {
public:
    int id;
    string company;
    string model;
    double rentPerDay;
    bool available;

    Car() {}

    Car(int i, string c, string m, double r, bool a) {
        id = i;
        company = c;
        model = m;
        rentPerDay = r;
        available = a;
    }
};

vector<Car> cars;

void loadCars() {
    cars.clear();

    ifstream file("cars.txt");

    if (!file)
        return;

    Car car;

    while (file >> car.id >> car.company >> car.model >> car.rentPerDay >> car.available) {
        cars.push_back(car);
    }

    file.close();
}

void saveCars() {

    ofstream file("cars.txt");

    for (Car car : cars) {
        file << car.id << " "
             << car.company << " "
             << car.model << " "
             << car.rentPerDay << " "
             << car.available << endl;
    }

    file.close();
}

bool idExists(int id) {

    for (Car car : cars)
        if (car.id == id)
            return true;

    return false;
}

void addCar() {

    Car car;

    cout << "\nEnter Car ID : ";
    cin >> car.id;

    if (idExists(car.id)) {
        cout << "Car ID already exists.\n";
        return;
    }

    cout << "Company : ";
    cin >> car.company;

    cout << "Model : ";
    cin >> car.model;

    cout << "Rent Per Day : ";
    cin >> car.rentPerDay;

    car.available = true;

    cars.push_back(car);

    saveCars();

    cout << "\nCar Added Successfully.\n";
}

void displayCars() {

    if (cars.empty()) {
        cout << "\nNo Cars Available.\n";
        return;
    }

    cout << "\n-------------------------------------------------------------\n";

    cout << left
         << setw(8) << "ID"
         << setw(15) << "Company"
         << setw(15) << "Model"
         << setw(12) << "Rent/Day"
         << setw(10) << "Status" << endl;

    cout << "-------------------------------------------------------------\n";

    for (Car car : cars) {

        cout << left
             << setw(8) << car.id
             << setw(15) << car.company
             << setw(15) << car.model
             << setw(12) << car.rentPerDay
             << setw(10) << (car.available ? "Available" : "Rented")
             << endl;
    }
}

void searchCar() {

    int id;

    cout << "\nEnter Car ID : ";
    cin >> id;

    for (Car car : cars) {

        if (car.id == id) {

            cout << "\nCar Found\n";

            cout << "Company : " << car.company << endl;
            cout << "Model : " << car.model << endl;
            cout << "Rent/Day : " << car.rentPerDay << endl;
            cout << "Status : "
                 << (car.available ? "Available" : "Rented")
                 << endl;

            return;
        }
    }

    cout << "Car Not Found.\n";
}

void rentCar() {

    int id;

    cout << "\nEnter Car ID : ";
    cin >> id;

    for (Car &car : cars) {

        if (car.id == id) {

            if (!car.available) {
                cout << "Car Already Rented.\n";
                return;
            }

            int days;

            cout << "Enter Number of Days : ";
            cin >> days;

            double bill = days * car.rentPerDay;

            car.available = false;

            saveCars();

            cout << "\nCar Rented Successfully.\n";

            cout << "Total Bill : Rs. " << bill << endl;

            return;
        }
    }

    cout << "Car Not Found.\n";
}

void returnCar() {

    int id;

    cout << "\nEnter Car ID : ";
    cin >> id;

    for (Car &car : cars) {

        if (car.id == id) {

            if (car.available) {
                cout << "Car Already Available.\n";
                return;
            }

            car.available = true;

            saveCars();

            cout << "Car Returned Successfully.\n";

            return;
        }
    }

    cout << "Car Not Found.\n";
}

void deleteCar() {

    int id;

    cout << "\nEnter Car ID : ";
    cin >> id;

    for (int i = 0; i < cars.size(); i++) {

        if (cars[i].id == id) {

            cars.erase(cars.begin() + i);

            saveCars();

            cout << "Car Deleted Successfully.\n";

            return;
        }
    }

    cout << "Car Not Found.\n";
}

int main() {

    loadCars();

    int choice;

    do {

        cout << "\n";
        cout << "=====================================\n";
        cout << "      CAR RENTAL MANAGEMENT SYSTEM\n";
        cout << "=====================================\n";

        cout << "1. Add Car\n";
        cout << "2. Display Cars\n";
        cout << "3. Search Car\n";
        cout << "4. Rent Car\n";
        cout << "5. Return Car\n";
        cout << "6. Delete Car\n";
        cout << "7. Exit\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice) {

        case 1:
            addCar();
            break;

        case 2:
            displayCars();
            break;

        case 3:
            searchCar();
            break;

        case 4:
            rentCar();
            break;

        case 5:
            returnCar();
            break;

        case 6:
            deleteCar();
            break;

        case 7:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "Invalid Choice.\n";
        }

    } while (choice != 7);

    return 0;
}
