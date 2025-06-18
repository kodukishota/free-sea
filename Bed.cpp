#include "Bed.h"
#include "LoadPlayer.h"

Bed::Bed(LoadPlayer* player) : Actor3D("Bed"),
	m_model(MV1LoadModel("Resource/Tree/tree.mv1")),
	m_canSleep(false),
	m_player(player)
{
	
}

void Bed::Update()
{

}