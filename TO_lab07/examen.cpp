#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <thread>
#include <mutex>
#include <algorithm>

std::mutex mtx; // Mutex for thread-safe operations

// User ratings structure
struct UserRating {
    int item;
    float rating;
};

// Function to read ratings from a CSV file
std::unordered_map<int, std::vector<UserRating>> readRatings(const std::string& filename) {
    std::unordered_map<int, std::vector<UserRating>> ratings;
    std::ifstream file(filename);
    std::string line, token;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<std::string> tokens;
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        int user = std::stoi(tokens[0]);
        int item = std::stoi(tokens[1]);
        float rating = std::stof(tokens[2]);
        ratings[user].push_back({item, rating});
    }

    return ratings;
}

// Function to calculate Manhattan distance
float manhattanDistance(const std::vector<UserRating>& user1Ratings, const std::vector<UserRating>& user2Ratings) {
    float distance = 0.0;
    for (const auto& rating1 : user1Ratings) {
        for (const auto& rating2 : user2Ratings) {
            if (rating1.item == rating2.item) {
                distance += std::abs(rating1.rating - rating2.rating);
                break;
            }
        }
    }
    return distance;
}

// Function to calculate Euclidean distance
float euclideanDistance(const std::vector<UserRating>& user1Ratings, const std::vector<UserRating>& user2Ratings) {
    float distance = 0.0;
    for (const auto& rating1 : user1Ratings) {
        for (const auto& rating2 : user2Ratings) {
            if (rating1.item == rating2.item) {
                distance += std::pow(rating1.rating - rating2.rating, 2);
                break;
            }
        }
    }
    return std::sqrt(distance);
}

// Function to find the top 3 similar users to a given user
std::vector<int> findTopSimilarUsers(const int targetUser, const std::unordered_map<int, std::vector<UserRating>>& ratings) {
    std::vector<std::pair<int, float>> similarityScores;

    for (const auto& userRatings : ratings) {
        if (userRatings.first != targetUser) {
            float distance = manhattanDistance(ratings.at(targetUser), userRatings.second);
            // Aplicar la condición de no considerar calificaciones con valor 0
            bool hasZeroRating = false;
            for (const auto& rating : userRatings.second) {
                if (rating.rating == 0) {
                    hasZeroRating = true;
                    break;
                }
            }
            if (distance != 0 && !hasZeroRating) {
                similarityScores.push_back({userRatings.first, distance});
            }
        }
    }

    std::sort(similarityScores.begin(), similarityScores.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    std::vector<int> topUsers;
    for (const auto& score : similarityScores) {
        topUsers.push_back(score.first);
        if (topUsers.size() >= 3) {
            break;
        }
    }
    return topUsers;
}

int main() {
    const std::string filename = "ratings_s.csv";
    auto ratings = readRatings(filename);

    // Parallel computation using threads
    std::thread manhattanThread([&] {
        float distance1 = manhattanDistance(ratings[20], ratings[32]);
        mtx.lock();
        std::cout << "a) distancia manhattan entre los usuarios 20 y 32: " << distance1 << std::endl;
        mtx.unlock();
    });

    std::thread euclideanThread([&] {
        float distance2 = euclideanDistance(ratings[20], ratings[32]);
        mtx.lock();
        std::cout << "b) distancia euclides entre los usuarios 20 y 32: " << distance2 << std::endl;
        mtx.unlock();
    });

    std::thread similarUsersThread([&] {
        auto similarUsers = findTopSimilarUsers(57, ratings);
        mtx.lock();
        std::cout << "c).- usuario 57, los tres usuarios más cercanos en preferencias ";
        for (int user : similarUsers) {
            std::cout << user << " ";
        }
        std::cout << std::endl;
        mtx.unlock();
    });

    manhattanThread.join();
    euclideanThread.join();
    similarUsersThread.join();

    return 0;
}
