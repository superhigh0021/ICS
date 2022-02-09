#include "AndQuery.h"
#include "NotQuery.h"
#include "OrQuery.h"
#include "Query.h"

int main(void) {
    ifstream file("text.txt");
    Query q=Query("mean");
    cout<<q<<endl;
    print(cout,q.eval(file));
    return 0;
}