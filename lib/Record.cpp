#include "Record.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Record::Record() {
    memset(&begin_time, 0, sizeof(begin_time));
    memset(&end_time, 0, sizeof(end_time));
}

void Record::initTags(string tags) {
    int I = 0;
    do {
        if(!tags.length())  break;

        I = tags.find("&");

        (this->tags).push_back(tags.substr(0, I));

        if(I == -1)
            tags = "";
        else 
            tags.erase(0, I+1);

    }while(true);
}

Record::Record(int id, string name, int year, int mon, int day, int begin_h, int begin_m, int end_h, int end_m, string tags, double nums, string comment) : id(id), name(name), nums(nums), comment(comment) {
    initTm(begin_time, year, mon, day, begin_h, begin_m);
    initTm(end_time, year, mon, day, end_h, end_m);

    initTags(tags);
}

void Record::setYear(int y) {
    begin_time.tm_year = end_time.tm_year = y - 1900;
}
int Record::getYear() const {
    return begin_time.tm_year + 1900;
}

void Record::setMonth(int m) {
    begin_time.tm_mon = end_time.tm_mon = m - 1;
}
int Record::getMonth() const {
    return begin_time.tm_mon + 1;
}

void Record::setDay(int d) {
    begin_time.tm_mday = end_time.tm_mday = d;
}
int Record::getDay() const {
    return begin_time.tm_mday;
}

void Record::setBeginH(int bh) {
    begin_time.tm_hour = bh;
}
int Record::getBeginH() const {
    return begin_time.tm_hour;
}
void Record::setBeginM(int bm) {
    begin_time.tm_min = bm;
}
int Record::getBeginM() const {
    return begin_time.tm_min;
}
void Record::setEndH(int eh) {
    end_time.tm_hour = eh;
}
int Record::getEndH() const {
    return end_time.tm_hour;
}
void Record::setEndM(int em) {
    end_time.tm_min = em;
}
int Record::getEndM() const {
    return end_time.tm_min;
}

void Record::setBeginTime(int year, int mon, int day, int h, int m) {
    initTm(begin_time, year, mon, day, h, m);
}
void Record::setEndTime(int year, int mon, int day, int h, int m) {
    initTm(end_time, year, mon, day, h, m);
}
void Record::initTm(tm &tim, int year, int mon, int day, int h, int m) {
    tim.tm_year = year - 1900;
    tim.tm_mon = mon - 1; // !!
    tim.tm_mday = day;
    tim.tm_hour = h;
    tim.tm_min  = m;
    tim.tm_sec = 0;
}

pair<int, int> Record::getInterval() {
    time_t begin = mktime(&begin_time);
    time_t end = mktime(&end_time);

    time_t interval = (end >= begin ? end - begin : 0) / 60;
    return make_pair(interval / 60, interval % 60);
}

bool Record::isThisDay(int y, int m, int d) {
    return y == begin_time.tm_year + 1900 && \
              m == begin_time.tm_mon + 1 && \
              d == begin_time.tm_mday;
}

void Record::setName(string name) {
    this->name = name;
}
string Record::getName() const {
    return name;
}

void Record::setComment(string comment) {
    this->comment = comment;
}
string Record::getComment() const {
    return comment;
}

void Record::setNums(double ns) {
    nums = ns;
}
double Record::getNums() const {
    return nums;
}


bool Record::hasTag(string tag) {
    return find(tags.begin(), tags.end(), tag) != tags.end();
}
void Record::addTag(string tag) {
    if(!hasTag(tag))
        tags.push_back(tag);
}
string Record::getTagsAsString() const{
    string res = "";
    if(tags.size()) 
        res = tags[0];
    for(int I = 1; I < tags.size(); I++){
        res += "&";
        res += tags[I];
    }
    return res;
}
string Record::getStringWithoutId() const {
    stringstream out;
    out << "\"" << name << "\",";
    out << begin_time.tm_year + 1900 << ",";
    out << begin_time.tm_mon + 1 << ",";
    out << begin_time.tm_mday << ",";
    out << begin_time.tm_hour << ",";
    out << begin_time.tm_min << ",";
    out << end_time.tm_hour << ",";
    out << end_time.tm_min << ",";
    out << "\"" << getTagsAsString() << "\",";
    out << nums << ",";
    out << "\"" << comment << "\"";

    return out.str();
}
