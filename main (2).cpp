#include <iostream>
#include <cmath>
#include "dictionary.h"
#include "binaryTree.h"
using namespace std;

// Function to convert degrees, minutes, and seconds to decimal degrees
double dmsToDecimal(double degrees, double minutes, double seconds, char direction) {
    double decimalDegrees = degrees + (minutes / 60.0) + (seconds / 3600.0);
    if (direction == 'S' || direction == 'W') {
        decimalDegrees = -decimalDegrees; // For South (S) latitudes and West (W) longitudes
    }
    return decimalDegrees;
}

double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double radiusEarth = 6371.137; // Mean Earth's radius in kilometers

    lat1 = lat1 * M_PI / 180.0;
    lon1 = lon1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;
    lon2 = lon2 * M_PI / 180.0;

    double diffLat = lat2 - lat1;
    double diffLon = lon2 - lon1;
    double a = sin(diffLat / 2) * sin(diffLat / 2) + cos(lat1) * cos(lat2) * sin(diffLon / 2) * sin(diffLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = radiusEarth * c;

    return distance;
}

int main() {
    Dictionary dict;
    bool running = true;

    while (running) {
        cout << "Dictionary Application Menu:"<<endl;
        cout << "1. Generate the dictionary in memory"<<endl;
        cout << "2. Save the dictionary to disk as a text file"<<endl;
        cout << "3. Download a dictionary from disk into memory (as a BST)"<<endl;
        cout << "4. Update the dictionary with added cities"<<endl;
        cout << "5. Search for a city in the dictionary"<<endl;
        cout << "6. List all dictionary entries"<<endl;
        cout << "7. Calculate distance between two cities"<<endl;
        cout << "8. Exit"<<endl;
        cout << "Enter your choice:"<<endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string filename;
                cout << "Enter the CSV file name to generate the dictionary from: ";
                cin >> filename;
                dict.generateDic(filename);
                break;
            }
            case 2: {
                string filename;
                cout << "Enter the text file name to save the dictionary: ";
                cin >> filename;
                dict.saveDic(filename);
                break;
            }
            case 3: {
                string filename;
                cout << "Enter the text file name to download the dictionary from: ";
                cin >> filename;
                dict.downloadDic(filename);
                break;
            }
            case 4: {
                CityEntry city;
                cout << "Enter the city details (Name Latitude Longitude Country): ";
                cin >> city.cityName >> city.latitude >> city.longitude >> city.country;
                dict.updateDic(city);
                cout << "City added to the dictionary"<<endl;
                break;
            }
            case 5: {
                string cityName;
                CityEntry result;
                cout << "Enter the city name to search for: ";
                cin >> cityName;
                if (dict.searchCity(cityName, result)) {
                    cout << "City: " << result.cityName << ", Latitude: " << result.latitude
                        << ", Longitude: " << result.longitude << ", Country: " << result.country << std::endl;
                } else {
                    cout << "City not found in the dictionary"<<endl;
                }
                break;
            }
            case 6: {
                cout << "Listing all dictionary entries:"<<endl;
                dict.list();
                break;
            }
            case 7: {
                
                double lat1, lon1, lat2, lon2;
                cout << "Enter coordinates for City 1 (Latitude, Longitude in DMS format):\n";
                double latDeg1, latMin1, latSec1;
                char latDir1;
                double lonDeg1, lonMin1, lonSec1;
                char lonDir1;
                cout << "Latitude (degrees minutes seconds direction): ";
                cin >> latDeg1 >> latMin1 >> latSec1 >> latDir1;
                cout << "Longitude (degrees minutes seconds direction): ";
                cin >> lonDeg1 >> lonMin1 >> lonSec1 >> lonDir1;

                cout << "Enter coordinates for City 2 (Latitude, Longitude in DMS format):\n";
                double latDeg2, latMin2, latSec2;
                char latDir2;
                double lonDeg2, lonMin2, lonSec2;
                char lonDir2;
                cout << "Latitude (degrees minutes seconds direction): ";
                cin >> latDeg2 >> latMin2 >> latSec2 >> latDir2;
                cout << "Longitude (degrees minutes seconds direction): ";
                cin >> lonDeg2 >> lonMin2 >> lonSec2 >> lonDir2;

                lat1 = dmsToDecimal(latDeg1, latMin1, latSec1, latDir1);
                lon1 = dmsToDecimal(lonDeg1, lonMin1, lonSec1, lonDir1);
                lat2 = dmsToDecimal(latDeg2, latMin2, latSec2, latDir2);
                lon2 = dmsToDecimal(lonDeg2, lonMin2, lonSec2, lonDir2);

                double distance = calculateDistance(lat1, lon1, lat2, lon2);

                cout << "The distance between the two cities is approximately " << distance << " kilometers." <<endl;
                break;
            }
            case 8: {
                running = false;
                break;
            }
            default: {
                cout << "Invalid choice. Please select a valid option"<<endl;
                break;
            }
        }
    }

    return 0;
}