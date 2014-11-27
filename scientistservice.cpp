#include "scientistservice.h"

ScientistService::ScientistService()
{
    scientistRepository = ScientistRepository();
}

void ScientistService::add(Scientist s) {
    scientistRepository.add(s);
}

vector<Scientist> ScientistService::list(SortField field, SortOrder order){
    sort( values.begin( ), values.end( ), [ ]( const MyStruct& lhs, const MyStruct& rhs )
    {
       return lhs.key < rhs.key;
    });
}
