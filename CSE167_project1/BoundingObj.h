//
//  BoundingObj.h
//  CSE167_project1
//
//  Created by Matthew Ma on 12/10/20.
//

#ifndef BoundingObj_h
#define BoundingObj_h
class BoundingObj{
public:
    int index;
protected:
    virtual bool notTouching(BoundingObj * obj, int type) = 0;
};

#endif /* BoundingObj_h */
