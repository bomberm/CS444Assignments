#pragma once
#include <iostream>
#include <stdlib.h>
#include <forward_list>
#include "listHandler.h"
#include "sharedResource.h"

void consumeResource(SharedResource *resource);

void inserter(ListHandler *list, int newElement);

void searcher(ListHandler *list, int num);

void deleter(ListHanlder *list, int num);
