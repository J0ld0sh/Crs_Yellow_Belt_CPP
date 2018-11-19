#include "bus_manager.h"

void BusManager::AddBus(const string &bus, const vector <string> &stops) {
    bfs[bus] = stops;
    for (const auto &item : stops) {
        sfb[item].push_back(bus);
    };
}

BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const {
    BusesForStopResponse b;
    if (sfb.count(stop) != 0) {
        b.buses = sfb.at(stop);
    }
    return b;
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const {
    StopsForBusResponse s;
    if (bfs.count(bus) != 0) {
        s.bus = bus;
        s.stops = bfs.at(bus);
        s.buses = sfb;
    }
    return s;
}

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse all;
    all.buses = bfs;
    return all;
}