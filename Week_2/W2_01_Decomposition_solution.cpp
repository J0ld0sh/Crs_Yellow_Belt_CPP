#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum class QueryType { NewBus, BusesForStop, StopsForBus, AllBuses };

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream &operator>>(istream &is, Query &q) {
	// Реализуйте эту функцию
	string type;
	is >> type;

	if (type == "NEW_BUS") {
		q.type = QueryType::NewBus;
		is >> q.bus;
		int cnt;
		is >> cnt;
		q.stops.resize(cnt);
		for (string &stop : q.stops) {
			is >> stop;
		}
	} else if (type == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	} else if (type == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	} else if (type == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}

	return is;
}

ostream &operator<<(ostream &os, Query &q) {
	os << "Code op: " << static_cast<int>(q.type) << " | Bus is: " << q.bus
	   << " | Stops for him: ";
	for (const auto &item : q.stops) {
		os << item << " ";
	}
}

struct BusesForStopResponse {
	vector<string> buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
	if(r.buses.empty()) {
		os << "No stop" << endl;
	} else {
		for (const string &bus : r.buses) {
			os << bus << " ";
		}
		os << endl;
	}
	return os;
}

struct StopsForBusResponse {
	string bus;
	vector<string> stops;
	map<string, vector<string>> buses;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r) {
	if(r.stops.empty()) {
		os << "No bus" << endl;
	} else {
		for (const string &stop : r.stops) {
			os << "Stop " << stop << ": ";
			if(r.buses.at(stop).size() == 1) {
				os << "no interchange";
			} else {
				for (const string& other_bus : r.buses.at(stop)) {
					if(r.bus != other_bus) {
						os << other_bus << " ";
					}
				}
			}
			os << endl;
		}
	}
	return os;
}

struct AllBusesResponse {
	map<string, vector<string>> buses;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r) {
	if(r.buses.empty()) {
		os << "No buses" << endl;
	} else {
		for (const auto& bus_item : r.buses) {
			os << "Bus " << bus_item.first << ": ";
			for (const string& stop : bus_item.second) {
				os << stop << " ";
			}
			os << endl;
		}
	}
	return os;
}

class BusManager {
public:
	void AddBus(const string &bus, const vector<string> &stops) {
		bfs[bus] = stops;
		for(const auto& item : stops) {
			sfb[item].push_back(bus);
		};
	}

	BusesForStopResponse GetBusesForStop(const string &stop) const {
		BusesForStopResponse b;
		if(sfb.count(stop) != 0) {
			b.buses = sfb.at(stop); 
		}
		return b; 
	}

	StopsForBusResponse GetStopsForBus(const string &bus) const {
		StopsForBusResponse s;
		if(bfs.count(bus) != 0) {
			s.bus = bus;
			s.stops = bfs.at(bus);
			s.buses = sfb;
		}
		return s;
	}

	AllBusesResponse GetAllBuses() const {
		AllBusesResponse all;
		all.buses = bfs;
		return all;
	}
private:
	map<string, vector<string>> bfs;
	map<string, vector<string>> sfb;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
	}

	return 0;
}