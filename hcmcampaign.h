/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 2
 * Programming Fundamentals Spring 2025
 * Date: 02.02.2025
 */

// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_HCM_CAMPAIGN_H_
#define _H_HCM_CAMPAIGN_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class Unit;
class UnitList;
class B;
class TerrainElement;

class Vehicle;
class Infantry;

class LiberationArmy;
class ARVN;

class Position;

class Road;
class Mountain;
class River;
class Urban;
class Fortification;
class SpecialZone;

class BattleField;

class HCMCampaign;
class Configuration;

enum VehicleType
{
    TRUCK, 
    MORTAR,
    ANTIAIRCRAFT,
    ARMOREDCAR,
    APC,
    ARTILLERY,
    TANK
};
enum InfantryType
{
    SNIPER,
    ANTIAIRCRAFTSQUAD,
    MORTARSQUAD,
    ENGINEER,
    SPECIALFORCES,
    REGULARINFANTRY
};

class Army
{
protected:
    int LF, EXP;
    string name;
    UnitList *unitList;
    BattleField *battleField;

public:
    Army();
    Army(Unit **unitArray, int size, string name, BattleField *battleField);
    virtual void fight(Army *enemy, bool defense = false) = 0;
    virtual string str() const = 0;
    void make();
    int get_EXP();
    int get_LF();
    void set_LF(int x);
    void set_EXP(int x);
    UnitList* get_unitList();
    virtual bool isLiberationArmy() const = 0;
    virtual bool isARVN() const = 0;
    bool special_num(int n, int x);
};

class LiberationArmy : public Army
{
public:
    LiberationArmy(Unit **unitArray, int size, string name, BattleField *battlefield);
    void fight(Army *enemy, bool defense = false) override;
    string str() const override;
    LiberationArmy(Unit **unit);
    vector <Unit*> sort_vector(vector <Unit*> v);
    void delete_set(vector <Unit*> v);
    bool isLiberationArmy() const override;
    bool isARVN() const override;
    long long updateToFibo(int x);
    long long lowerbound(int x, long long f[]);
};

class ARVN : public Army{
public:
    ARVN(Unit ** unitArray, int size, string name, BattleField *battleField);
    void fight(Army *enemy, bool defense = false) override;
    string str() const override;
    bool isLiberationArmy() const override;
    bool isARVN() const override;
};

class Position
{
private:
    int r, c;

public:
    Position(int r = 0, int c = 0);
    Position(const string &str_pos); // Example: str_pos = "(1,15)"
    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    string str() const; // Example: returns "(1,15)"
    double distance(Position a, Position b);
};

class Unit
{
protected:
    int quantity, weight;
    Position pos;

public:
    Unit(int quantity, int weight, Position pos);
    virtual ~Unit();
    virtual int getAttackScore() = 0;
    Position getCurrentPosition() const;
    virtual string str() const = 0;
    virtual bool isInfantry() const = 0;
    virtual bool isVehicle() const = 0;
    int get_weight();
    int get_quantity();
    void set_quantity(int x);
    void set_weight(int x);
    void set_pos(Position pos);
    virtual InfantryType getInfantryType() const = 0;
    virtual VehicleType getVehicleType() const = 0;
    virtual Unit* clone() const = 0;
};

struct Node
{
    Unit *data;
    Node *next;
};

class UnitList
{
private:
    int capacity;
    // TODO
    Node *head;

public:
    UnitList(int capacity);
    UnitList();
    bool insert(Unit *unit);                   // return true if insert successfully
    bool isContain(VehicleType vehicleType);   // return true if it exists
    bool isContain(InfantryType infantryType); // return true if it exists
    string str() const;
    // TODO
    Node *makeNode(Unit *unit);
    void deleteNode(Node *x);
    int size_of_list();
    Node *get_head();
    bool Unit_exist(Unit *unit);
    void set_capacity(int x);
    int get_capacity();
    void set_head(Node* newHead);
};

class TerrainElement
{
public:
    TerrainElement();
    ~TerrainElement();
    virtual void getEffect(Army *army) = 0;
    virtual Position get_pos() const = 0;
    virtual string str() const = 0;
};

class Road : public TerrainElement{
private: 
    Position pos;
public: 
    void getEffect(Army *army) override;
    string str() const override;
    Position get_pos() const override;
};

class Mountain : public TerrainElement{
private: 
    Position pos;
public:
    void getEffect(Army *army) override;
    Position get_pos() const override;
    string str() const override;
};

class River : public TerrainElement{
private:
    Position pos;
public:
    void getEffect(Army *army) override;
    Position get_pos() const override;
    string str() const override;
};

class Urban : public TerrainElement{
private:
    Position pos;
public:     
    void getEffect(Army*army) override;
    Position get_pos() const override;
    string str() const override;
};

class Fortification : public TerrainElement{
private:
    Position pos;
public: 
    void getEffect(Army *army) override;
    Position get_pos() const override;
    string str() const override;
};

class SpecialZone : public TerrainElement{
private:
    Position pos;
public:
    void getEffect(Army *army) override;
    Position get_pos() const override;
    string str() const override;
};

class BattleField
{
private:
    int n_rows, n_cols;
    // TODO
    TerrainElement ***terrain;
public:
    BattleField(int n_rows, int n_cols, vector<Position *> arrayForest,
                vector<Position *> arrayRiver, vector<Position *> arrayFortification,
                vector<Position *> arrayUrban, vector<Position *> arraySpecialZone);
    ~BattleField();
    string str();
    int getRow();
    int getCols();
    TerrainElement*** getTerrain();
};

class HCMCampaign
{
private:
    Configuration *config;
    BattleField *battleField;
    LiberationArmy *liberationArmy;
    ARVN *arvn;

public:
    HCMCampaign(const string &config_file_path);
    void run();
    string printResult();
};

class Configuration{
private:
    int num_rows, num_cols;
    vector <Position*>  arrayForest, 
                        arrayRiver, 
                        arrayFortification, 
                        arrayUrban, 
                        arraySpecialZone;
    vector <Unit*> liberationUnits;
    vector <Unit*> ARVNUnits;
    int eventCode;
public:
    Configuration(const string &filepath);
    ~Configuration();
    string str() const;
    InfantryType string_to_enumI(string type);
    VehicleType string_to_enumV(string type);
    // Getter cho số dòng, số cột và mã sự kiện
    int getNumRows() const;
    int getNumCols() const;
    int getEventCode() const;

    // Getter cho các khu vực đặc biệt
    const vector<Position*>& getArrayForest() const;
    const vector<Position*>& getArrayRiver() const;
    const vector<Position*>& getArrayFortification() const;
    const vector<Position*>& getArrayUrban() const;
    const vector<Position*>& getArraySpecialZone() const;

    // Getter cho các đơn vị
    const vector<Unit*>& getLiberationUnits() const;
    const vector<Unit*>& getARVNUnits() const;

};

class Vehicle : public Unit
{
private:
    VehicleType vehicleType;

public:
    Vehicle(int quantity, int weight, const Position pos, VehicleType vehicleType);
    virtual int getAttackScore();
    string str() const override;
    bool isInfantry() const override;
    bool isVehicle() const override;
    VehicleType getVehicleType() const override;
    InfantryType getInfantryType() const override;
    Unit* clone() const override;
};

class Infantry : public Unit
{
private:
    InfantryType infantryType;

public:
    Infantry(int quantity, int weight, const Position pos, InfantryType infantryType);
    int getAttackScore();
    string str() const override;
    int sum_digit(int n);
    int getScore(int quantity, int weight);
    bool isInfantry() const override;
    bool isVehicle() const override;
    InfantryType getInfantryType() const override;
    VehicleType getVehicleType() const override;
    Unit* clone() const override;
};

#endif