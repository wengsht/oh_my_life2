## Time manager

### Base on
1. QT Libraries
2. sqlite3

### install  
It is developing right now... 

for test, you can:

1. install QT

2. use include/SQLITE.sql to build the table in your sqlite3. and then:

3. build oh-my-life2:
```
    cd src/
    mkdir build
    cd build
    qmake ../ (for mac, qmake -spec macx-g++ ../)
    make 
```
    
### nowon

You can record something right now, but the statistics Widget is developing...

### usage
Record:

1. name : string 
1. begin_h/begin_m/end_h/end_m : 0-23 0-59..
1. tags: eg. 

```
    xx&yy&z
```

has three tags [xx][yy][z]

1. nums : double
1. comment : string
