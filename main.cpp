#include <iostream>

#include "items.h"
#include "map/noise_mask.h"
#include "map/rolling_particles_mask.h"
#include "worldmap.h"

using namespace std;

int main()
{
    cout << "Simple Roguelike Game by Fantik (c) 2014" << endl;

    CWorldMap *wm=new CWorldMap(80,25);
    wm->Generate();
    wm->Dump();

    delete wm;

    return 0;
}
