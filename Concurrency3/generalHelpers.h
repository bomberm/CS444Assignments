#pragma once
#include <iostream>
#include <stdlib.h>
#include "listHandler.h"
#include "sharedResource.h"

void consumeResource(SharedResource *resource);

void inserter(ListHandler *list, int newElement);

void searcher(ListHandler *list, int num);

void deleter(ListHandler *list, int num);
