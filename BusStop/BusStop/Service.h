#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <math.h>

using namespace std;

#define ONE_HOUR 60
#define DAY 1440
#define BAD_DATA "Incorrect original data!"

#define GROTTY "Grotty"
#define POSH "Posh"

#define END_OF_STREAM ""



class HMTime {

private:

	time_t time_;	

public:
	
	HMTime();
	HMTime(string hm_str);
	HMTime(time_t minutes);
	static time_t toTimeInMinutes(int hours, int minutes);
	time_t getTimeInMinutes();
	bool operator==(HMTime other);
	bool operator>(HMTime other);
	bool operator<(HMTime other); 
	time_t operator-(HMTime other);
	HMTime operator+(HMTime other);
	bool operator<=(time_t minutes);

	friend ostream& operator<< (ostream& out, HMTime& hm_time);
	friend istream& operator>> (istream& in, HMTime& hm_time);	
};


time_t HMTime::toTimeInMinutes(int hours, int minutes) {

	return (time_t)hours * (time_t)ONE_HOUR + (time_t)minutes;
}

time_t HMTime::getTimeInMinutes() {

	return time_;
}

HMTime::HMTime() : time_(0) {};

HMTime::HMTime(time_t minutes) {

	time_ = minutes;
}

HMTime::HMTime(string hm_str) : HMTime() {

	const short number_size = 3;
	char buf[number_size] = "";
	int i, j, k = 0;
	int hours, minutes;

	for (i = 0; i < hm_str.size(); i++) {

		if (hm_str[i] == ':') {

			buf[number_size - 1] = '\0';
			hours = atoi(buf);
			k = 0;

			for (j = i + 1; j < hm_str.size(); j++) {

				if (k >= number_size) {

					throw out_of_range(BAD_DATA);
				};

				buf[k] = hm_str[j];
				k++;
			}

			buf[number_size - 1] = '\0';
			minutes = atoi(buf);
			break;
		}

		if (k >= number_size) {

			throw out_of_range(BAD_DATA);
		};

		buf[k] = hm_str[i];
		k++;
	}

	time_ = toTimeInMinutes(hours, minutes);
}

bool HMTime::operator==(HMTime other) {

	return this->time_ == other.time_;
}

bool HMTime::operator>(HMTime other) {

	return this->time_ > other.time_;
}

bool HMTime::operator<(HMTime other) {

	return this->time_ < other.time_;
}

HMTime HMTime::operator+(HMTime other) {

	return HMTime(this->time_ + other.time_);
}

time_t HMTime::operator-(HMTime other) {

	return this->time_ - other.time_;
}

bool HMTime::operator<=(time_t minutes) {

	return this->time_ <= minutes;
}


ostream& operator<< (ostream& out, HMTime& hm_time)
{
	out << setfill('0') << setw(2) << hm_time.time_ / ONE_HOUR << ":" << setw(2) << hm_time.time_ % ONE_HOUR;
	return out;
}

istream& operator>> (istream& in, HMTime& hm_time) {

	string hm_str;
	in >> hm_str;

	if (hm_str != END_OF_STREAM) hm_time = HMTime(hm_str);

	return in;
}



class TravelService
{
private:
	
	string company_;
	HMTime departure_time_;
	HMTime arrival_time_;
	bool is_selected_;

public:
	
	TravelService();
	TravelService(string, HMTime, HMTime);
	bool operator<(const TravelService &other);
	friend ostream& operator<< (ostream& out, TravelService& traveling);
	friend istream& operator>> (istream& in, TravelService& traveling);
	bool operator>(time_t minutes);
	bool operator==(TravelService& other);
	HMTime depature();
	HMTime arrival();
	string company();
	void Select();
	bool isSelected();
	bool midnight�rossing();
	
};

TravelService::TravelService()
{
	company_ = "";
	departure_time_ = HMTime();
	arrival_time_ = HMTime();
	is_selected_ = false;
}


TravelService::TravelService(string company, HMTime depature, HMTime arrival)
{
	this->company_ = company;
	departure_time_ = depature;
	arrival_time_ = arrival;
	is_selected_ = false;
}

bool TravelService::operator<(const TravelService &other) {

	return this->departure_time_ < other.departure_time_;
}


bool TravelService::operator>(time_t minutes) {

	if (midnight�rossing()) {
		
		return arrival_time_ + HMTime(DAY) - departure_time_ > minutes;
	}
	else {
	
		return arrival_time_ - departure_time_ > minutes;
	}	

}

bool TravelService::operator==(TravelService& other) {

	return company_ == other.company_ && departure_time_ == other.departure_time_ && arrival_time_ == other.arrival_time_;
}

bool TravelService::midnight�rossing() {

	return arrival_time_ < departure_time_;	
}

HMTime TravelService::depature() {

	return departure_time_;
}

HMTime TravelService::arrival() {

	return arrival_time_;
}

string TravelService::company() {

	return company_;
}

void TravelService::Select() {

	is_selected_ = true;
}

bool TravelService::isSelected() {

	return is_selected_;
}

ostream& operator<< (ostream& out, TravelService& traveling)
{
	out << traveling.company_ << " " << traveling.departure_time_ << " " << traveling.arrival_time_;
	return out;
}

istream& operator>> (istream& in, TravelService& traveling) {

	string company = "";
	HMTime depature, arrival;

	in >> company;
	in >> depature;
	in >> arrival;

	if (company != END_OF_STREAM) {
	
		traveling = TravelService(company, depature, arrival);
	}
	
	return in;
}


