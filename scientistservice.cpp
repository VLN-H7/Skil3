#include "scientistservice.h"

ScientistService::ScientistService()
{
    scientistRepository = ScientistRepository();
}

void ScientistService::add(Scientist s) {
    scientistRepository.add(s);
}

vector<Scientist> ScientistService::list(ScientistSort::SortField field, ScientistSort::SortOrder order){
    return scientistRepository.list(field,order);
}
