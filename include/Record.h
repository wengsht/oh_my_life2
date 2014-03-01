#ifndef __RECORD_H__
#define __RECORD_H__

#include <string>
#include <vector>
using namespace std;
#include "ctime"

class Record {
    public:
        Record();
        Record(int id, string name, int year, int mon, int day, int begin_h, int begin_m, int end_h, int end_m, string tags, double nums, string comment);
        pair<int, int> getInterval();

        void setName(string name);
        string getName() const;

        void setComment(string comment);
        string getComment() const;

        void setYear(int y);
        int getYear() const;

        void setMonth(int m);
        int getMonth() const;

        void setDay(int d);
        int getDay() const;

        void setBeginH(int bh);
        int getBeginH() const;

        void setBeginM(int bm);
        int getBeginM() const;

        void setEndH(int eh);
        int getEndH() const;

        void setEndM(int em);
        int getEndM() const;

        void setNums(double ns);
        double getNums() const;

        bool hasTag(string tag);
        void addTag(string tag);

        void initTags(string tags);

        bool isThisDay(int y, int m, int d);
        void setBeginTime(int year, int mon, int day, int h, int m);
        void setEndTime(int year, int mon, int day, int h, int m);

        string getTagsAsString() const;
        string getStringWithoutId() const;
    protected:
        friend class RecordPocket;
        void initTm(tm &tim, int year, int mon, int day, int h, int m);

        int id;
        string name;
        struct tm begin_time, end_time;
        vector<string> tags;
        double nums;
        string comment;
};

#endif
