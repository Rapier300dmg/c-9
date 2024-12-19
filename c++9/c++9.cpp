#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>

struct Passenger {
    double arrivalTime;
};

struct Minibus {
    double arrivalTime;
    int freeSeats;
};

void simulateBusStop(double avgPassengerInterval, double avgMinibusInterval, int maxQueueSize, bool isTerminal) {
    std::queue<Passenger> passengerQueue;
    std::vector<double> waitingTimes;
    std::srand(std::time(nullptr));

    double currentTime = 0.0;
    double nextPassengerTime = 0.0;
    double nextMinibusTime = avgMinibusInterval * (0.8 + ((double)std::rand() / RAND_MAX) * 0.4);

    while (currentTime < 120.0) { 
        currentTime += 0.1;

        if (currentTime >= nextPassengerTime) {
            if (passengerQueue.size() < maxQueueSize) {
                passengerQueue.push({ currentTime });
            }
            nextPassengerTime += avgPassengerInterval * (0.8 + ((double)std::rand() / RAND_MAX) * 0.4);
        }

        if (currentTime >= nextMinibusTime) {
            int availableSeats = std::rand() % 20 + 1;
            while (!passengerQueue.empty() && availableSeats > 0) {
                Passenger p = passengerQueue.front();
                passengerQueue.pop();
                waitingTimes.push_back(currentTime - p.arrivalTime);
                --availableSeats;
            }
            nextMinibusTime += avgMinibusInterval * (0.8 + ((double)std::rand() / RAND_MAX) * 0.4);
        }
    }

    double totalWaitingTime = 0.0;
    for (double wt : waitingTimes) {
        totalWaitingTime += wt;
    }

    std::cout << "\n--- Simulation Results ---\n";
    std::cout << "Total Passengers Served: " << waitingTimes.size() << std::endl;
    std::cout << "Average Waiting Time: " << (waitingTimes.empty() ? 0.0 : totalWaitingTime / waitingTimes.size()) << " minutes\n";
    std::cout << "Passengers Left in Queue: " << passengerQueue.size() << "\n";
}

struct PrintJob {
    int priority;
    std::string user;
    double timestamp;

    bool operator<(const PrintJob& other) const {
        return priority < other.priority;
    }
};

void simulatePrinterQueue() {
    std::priority_queue<PrintJob> printQueue;
    std::vector<PrintJob> printLog;

    printQueue.push({ 3, "User1", 1.0 });
    printQueue.push({ 1, "User2", 2.0 });
    printQueue.push({ 5, "User3", 3.0 });
    printQueue.push({ 2, "User4", 4.0 });

    while (!printQueue.empty()) {
        PrintJob job = printQueue.top();
        printQueue.pop();
        printLog.push_back(job);
        std::cout << "Printing job from " << job.user << " with priority " << job.priority << " at time " << job.timestamp << "\n";
    }

    std::cout << "\n--- Print Log ---\n";
    for (const PrintJob& job : printLog) {
        std::cout << "User: " << job.user << ", Priority: " << job.priority << ", Time: " << job.timestamp << "\n";
    }
}

int main() {
    std::cout << "Simulating bus stop...\n";
    simulateBusStop(1.0, 5.0, 10, false);

    std::cout << "\nSimulating printer queue...\n";
    simulatePrinterQueue();

    return 0;
}