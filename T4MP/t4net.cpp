#define _WINSOCKAPI_ 
#include "t4net.h"
#include <Ws2tcpip.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "Engine.h"

TurokEngine netEngine;
T4Engine * t4engine = (T4Engine*)0x6B52E4;

#pragma comment(lib,"ws2_32.lib")

const int port = 15001;

void T4Network::Initalize()
{

	server = (GetPrivateProfileIntA("T4MP", "server", 0, ".\\t4mp.ini") == 1);
	port = (u_short)GetPrivateProfileIntA("T4MP", "port", 15001, ".\\t4mp.ini");
	GetPrivateProfileStringA("T4MP", "server_ip", "127.0.0.1", (LPSTR)server_ip, INET_ADDRSTRLEN, ".\\t4mp.ini");
	

	printf("Reading 'server' entry: %i\r\n", GetPrivateProfileIntA("T4MP", "server", 0, ".\\t4mp.ini"));
	if (server)
		printf("We're the host\r\n");
	
	printf("Our port is %d\r\n", port);
	
	if (server_ip[0] != '\0' && server == false)
		printf("We're the client and we'll be connecting to the server %s\r\n", server_ip);

	WSADATA wsaData;
	WSAStartup(0x0202, &wsaData);
	memset((char*)&this->serverAddr, 0, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);
	serverSock = INVALID_SOCKET;


	int error = 0;
	this->serverSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (this->serverSock == INVALID_SOCKET)
	{
		printf("Failed to establish socket\r\n");
		this->Destroy();
		return;
	}

	 error = bind(serverSock, (LPSOCKADDR)&serverAddr, sizeof(serverAddr));

	 if (error == SOCKET_ERROR)
	 {
		 printf("error: bind() failed\r\n");
		 this->Destroy();
		 return;
	 }
	
	 unsigned long int nonBlockingMode = 1;
	 int result = ioctlsocket(serverSock, FIONBIO, &nonBlockingMode);

	 if (result)
	 {
		 printf("ioctlsocket failed\r\n");
		 this->Destroy();
	 }


	 printf("WinSock Intialized and bound to %d\r\n", port);
}

void T4Network::SendSnapShot()
{

	if (netplayers.size() == 0)
		return;

	Packet snappak;
	snappak.set_type(Packet_Type_server_snap);


	ServerSnap *server_snapshot = snappak.mutable_server_snapshot();
	server_snapshot->set_packet_sequence(snappack_sequence);

	/* We'll add the server player first... */
	ServerSnap_PlayerData *player_data = server_snapshot->add_player();
	ServerSnap_PlayerData_WeaponWheel *player_weaponwheel = player_data->mutable_weapons();
	DMPlayer* player = netEngine.GetDMPlayer(0);

	/* 
		Currently not calculating any delta we're just sending the info straight on...
		May be able to get away with it but it's not ideal at all, just a temporary solution along with other shit.
	 */

	if (player)
	{
		WeaponWheel* player_weapon = player->pWeaponWheel;

		player_data->set_index(0);
		if (player_weapon)
		{

			/* Spike Grenade*/
			player_weaponwheel->set_bhas_spikegrenade( (player_weapon->bHas_SpikeGrenade2 == 1) );
			player_weaponwheel->set_spikegrenade_ammo(player_weapon->SpikeGrenade_Ammo);

			/* Pistol */
			player_weaponwheel->set_bhas_pistol( (player_weapon->bHas_Pistol2 == 1) );
			player_weaponwheel->set_pistol_ammo(player_weapon->Pistol_Ammo);

			/* Shotgun */
			player_weaponwheel->set_bhas_shotgun( (player_weapon->bHas_ShotGun2 == 1) );
			player_weaponwheel->set_shotgun_ammo(player_weapon->ShotGun_Ammo);

			/* Flechetee */
			player_weaponwheel->set_bhas_flecheete( (player_weapon->bHas_Fleechete2 == 1) );
			player_weaponwheel->set_fleechete_ammo(player_weapon->Fleechete_Ammo);
			
			/* Flechetee - MiniGun */
			player_weaponwheel->set_minigun_ammo(player_weapon->MiniGun_Ammo);
			
			/* Rocket Launcher */
			player_weaponwheel->set_bhas_rocketlauncher( (player_weapon->bHas_RocketLauncher2 == 1) );
			player_weaponwheel->set_rocket_ammo1(player_weapon->RocketLauncher_Ammo);
			player_weaponwheel->set_rocket_ammo2(player_weapon->RocketLauncher_Ammo2);
			player_weaponwheel->set_rocket_ammo3(player_weapon->RocketLauncher_Ammo3);

			/* Plasma Cannon */
			player_weaponwheel->set_bhas_plasmacannon( (player_weapon->bHas_PlasmaCannon2 == 1 ) );
			player_weaponwheel->set_plasma_ammo1(player_weapon->PlasmaCannon_Ammo);
			player_weaponwheel->set_plasma_ammo2(player_weapon->PlasmaCannon_Ammo2);
			player_weaponwheel->set_plasma_ammo3(player_weapon->PlasmaCannon_Ammo3);

			/* Spider Mine  - disabled will prevent problems don't even allow the host to have it.*/
			player_weapon->bHas_SpiderMine = 0;
			player_weapon->bHas_SpiderMine2 = 0;
			player_weapon->SpiderMine_Ammo = 0;
			player_weaponwheel->set_spidermine_ammo(0);
			player_weaponwheel->set_bhas_spidermine(0);
		

			/* DarkMatter Cube */
			player_weaponwheel->set_bhas_darkmatter( (player_weapon->bHas_DarkMatterCube2 == 1 ) );
			player_weaponwheel->set_darkmatter_ammo(player_weapon->DarkMatterCube_Ammo);

			/* Cross Bow */
			player_weaponwheel->set_bhas_crossbow( ( player_weapon->bHas_CrossBow2 == 1 ) );
			player_weaponwheel->set_crossbow_normal_ammo(player_weapon->CrossBow_Normal_Ammo);
			player_weaponwheel->set_crossbow_explosive_ammo(player_weapon->CrossBow_Explosive_Ammo);
			player_weaponwheel->set_crossbow_poison_ammo(player_weapon->CrossBow_Poison_Ammo);
		}

		/*if (netEngine.)
			player_data->set_crouch(true);

		if (netEngine.jump_set)
			player_data->set_jump(true);
			*/

		if (fire_set)
		{
			player_data->set_fire(true);
		}

		if (fire_hold)
		{
			player_data->set_fire_hold(true);
			player_data->set_fire_hold_time(fire_hold_time);
		}

		if (fire_release)
		{
			player_data->set_fire_release(true);
			player_data->set_fire_release_time(fire_release_time);
		}


		/* POS Data */
		player_data->set_x(player->POS.x);
		player_data->set_y(player->POS.y);
		player_data->set_z(player->POS.z);
		
		player_data->set_viewx(player->ViewX);
		player_data->set_viewy(player->ViewY);
		
		player_data->set_walk_backward((player->Walk_backward > 0.0f));
		player_data->set_walk_forward((player->Walk_forward > 0.0f));
		player_data->set_walk_left((player->Walk_left > 0.0f));
		player_data->set_walk_right((player->Walk_right > 0.0f));
	
		player_data->set_max_health(player->pHealth->Max);
		player_data->set_current_health(player->pHealth->Current);

		if (player->pHealth->Current == 0.0f)
		{
			player_data->set_death_type(death_type);
		}

		player_data->set_weapon_slot(player->Weapon_slot);
		player_data->set_weapon_switch_time(player->Weapon_switch_time);
		player_data->set_weapon_switch(player->Weapon_switch);

		
	}
	/* We're gonna make some assumptions here we REALLY shouldn't */
	for (NetworkPlayer* update_player : netplayers)
	{
		player_data = server_snapshot->add_player();
		player_weaponwheel = player_data->mutable_weapons();
		DMPlayer* player = netEngine.GetDMPlayer(update_player->index);

		if (player)
		{
			WeaponWheel* player_weapon = player->pWeaponWheel;
			player_data->set_index(update_player->index);
			if (player_weapon)
			{

				/* Spike Grenade*/
				player_weaponwheel->set_bhas_spikegrenade((player_weapon->bHas_SpikeGrenade2 == 1));
				player_weaponwheel->set_spikegrenade_ammo(player_weapon->SpikeGrenade_Ammo);

				/* Pistol */
				player_weaponwheel->set_bhas_pistol((player_weapon->bHas_Pistol2 == 1));
				player_weaponwheel->set_pistol_ammo(player_weapon->Pistol_Ammo);

				/* Shotgun */
				player_weaponwheel->set_bhas_shotgun((player_weapon->bHas_ShotGun2 == 1));
				player_weaponwheel->set_shotgun_ammo(player_weapon->ShotGun_Ammo);

				/* Flechetee */
				player_weaponwheel->set_bhas_flecheete((player_weapon->bHas_Fleechete2 == 1));
				player_weaponwheel->set_fleechete_ammo(player_weapon->Fleechete_Ammo);

				/* Flechetee - MiniGun */
				player_weaponwheel->set_minigun_ammo(player_weapon->MiniGun_Ammo);

				/* Rocket Launcher */
				player_weaponwheel->set_bhas_rocketlauncher((player_weapon->bHas_RocketLauncher2 == 1));
				player_weaponwheel->set_rocket_ammo1(player_weapon->RocketLauncher_Ammo);
				player_weaponwheel->set_rocket_ammo2(player_weapon->RocketLauncher_Ammo2);
				player_weaponwheel->set_rocket_ammo3(player_weapon->RocketLauncher_Ammo3);

				/* Plasma Cannon */
				player_weaponwheel->set_bhas_plasmacannon((player_weapon->bHas_PlasmaCannon2 == 1));
				player_weaponwheel->set_plasma_ammo1(player_weapon->PlasmaCannon_Ammo);
				player_weaponwheel->set_plasma_ammo2(player_weapon->PlasmaCannon_Ammo2);
				player_weaponwheel->set_plasma_ammo3(player_weapon->PlasmaCannon_Ammo3);

				/* Spider Mine  - disabled will prevent problems don't even allow the host to have it.*/
				player_weapon->bHas_SpiderMine = 0;
				player_weapon->bHas_SpiderMine2 = 0;
				player_weapon->SpiderMine_Ammo = 0;
				player_weaponwheel->set_spidermine_ammo(0);
				player_weaponwheel->set_bhas_spidermine(0);


				/* DarkMatter Cube */
				player_weaponwheel->set_bhas_darkmatter((player_weapon->bHas_DarkMatterCube2 == 1));
				player_weaponwheel->set_darkmatter_ammo(player_weapon->DarkMatterCube_Ammo);

				/* Cross Bow */
				player_weaponwheel->set_bhas_crossbow((player_weapon->bHas_CrossBow2 == 1));
				player_weaponwheel->set_crossbow_normal_ammo(player_weapon->CrossBow_Normal_Ammo);
				player_weaponwheel->set_crossbow_explosive_ammo(player_weapon->CrossBow_Explosive_Ammo);
				player_weaponwheel->set_crossbow_poison_ammo(player_weapon->CrossBow_Poison_Ammo);
			}

			if (update_player->fire_set)
			{
				player_data->set_fire(true);
			}

			if (update_player->fire_hold)
			{
				player_data->set_fire_hold(true);
				player_data->set_fire_hold_time(update_player->fire_hold_time);
			}

			if (update_player->fire_release)
			{
				player_data->set_fire_release(true);
				player_data->set_fire_release_time(update_player->fire_release_time);
			}

			
			/*if (netEngine.crouch)
				player_data->set_crouch(true);

			if (netEngine.jump_set)
				player_data->set_jump(true);
			*/

		
			/* POS Data */
			player_data->set_x(player->POS.x);
			player_data->set_y(player->POS.y);
			player_data->set_z(player->POS.z);

			player_data->set_viewx(player->ViewX);
			player_data->set_viewy(player->ViewY);

			player_data->set_walk_backward((player->Walk_backward > 0.0f));
			player_data->set_walk_forward((player->Walk_forward > 0.0f));
			player_data->set_walk_left((player->Walk_left > 0.0f));
			player_data->set_walk_right((player->Walk_right > 0.0f));

			player_data->set_max_health(player->pHealth->Max);
			player_data->set_current_health(player->pHealth->Current);

			if (player->pHealth->Current == 0.0f)
			{
				player_data->set_death_type(update_player->death_type);
			}

			player_data->set_weapon_slot(player->Weapon_slot);
			player_data->set_weapon_switch_time(player->Weapon_switch_time);
			player_data->set_weapon_switch(player->Weapon_switch);

			


		}
		
	}

	/* Now that the entire packet has been built time to send it out to each individual player */

	char* SnapPacket = new char[snappak.ByteSize()];

	ZeroMemory(SnapPacket, snappak.ByteSize());

	snappak.SerializeToArray(SnapPacket, snappak.ByteSize());


	/* Re-loop the network array and start sending the packet out */
	for (NetworkPlayer* net_player : netplayers)
	{
		sockaddr_in playerAddr;
		playerAddr.sin_port = net_player->port; // This should already be in the correct order.
		playerAddr.sin_addr.s_addr = net_player->ipaddr;
		playerAddr.sin_family = AF_INET;

		sendto(serverSock, SnapPacket, snappak.ByteSize(), 0, (SOCKADDR*)&playerAddr, sizeof(playerAddr));

	}
	
	server_snapshot->Clear();
	snappak.Clear();

	delete[] SnapPacket;

	if (fire_release)
	{
		fire_set = false;
		fire_hold = false;
		fire_release = false;
	}

	for (NetworkPlayer* net_player : netplayers)
	{

		if (net_player->fire_release)
		{
			net_player->fire_hold = false;
			net_player->fire_release = false;
			net_player->fire_set = false;
		}

		/*sockaddr_in playerAddr;
		playerAddr.sin_port = net_player->port; // This should already be in the correct order.
		playerAddr.sin_addr.s_addr = net_player->ipaddr;
		playerAddr.sin_family = AF_INET;

		sendto(serverSock, SnapPacket, snappak.ByteSize(), 0, (SOCKADDR*)&playerAddr, sizeof(playerAddr));*/

	}

	snappack_sequence++;


}

void T4Network::ConnectToServer()
{
	printf("Sending connect packet to server %s:%d\r\n", server_ip, ntohs(serverAddr.sin_port));
	


	Packet SendingPak;
	SendingPak.set_type(Packet_Type_client_connect);

	char* ConnectPak = new char[SendingPak.ByteSize()];

	ZeroMemory(ConnectPak, SendingPak.ByteSize());

	SendingPak.SerializeToArray(ConnectPak, SendingPak.ByteSize());

	struct sockaddr_in send_to;
	send_to.sin_family = AF_INET;
	send_to.sin_port = htons(port);
	inet_pton(AF_INET, server_ip, &send_to.sin_addr.s_addr);


	int send = sendto(serverSock, ConnectPak, SendingPak.ByteSize(), 0, (LPSOCKADDR)&send_to, sizeof(send_to));
	if (send == SOCKET_ERROR)
	{
		printf("Socket error on send: %08X\r\n", WSAGetLastError());
	}

	SendingPak.Clear();
	delete[] ConnectPak;
}

void T4Network::SendPlayerSnapShot()
{
	Packet PlayerSnapPacket;
	PlayerSnapPacket.set_type(Packet_Type_client_snap);

	PlayerSnap *player_snap = PlayerSnapPacket.mutable_player_snapshot();
	DMPlayer* local_player = netEngine.GetDMPlayer(0);
	player_snap->set_packet_sequence(playersnap_pack_sequence);

	if (local_player)
	{
		player_snap->set_viewx(local_player->ViewX);
		player_snap->set_viewy(local_player->ViewY);
		
		player_snap->set_walk_backward((local_player->Walk_backward > 0.0f ));
		player_snap->set_walk_forward((local_player->Walk_forward > 0.0f ));
		player_snap->set_walk_left((local_player->Walk_left > 0.0f ));
		player_snap->set_walk_right((local_player->Walk_right > 0.0f ));

		player_snap->set_x(local_player->POS.x);
		player_snap->set_y(local_player->POS.y);
		player_snap->set_z(local_player->POS.z);

		player_snap->set_weapon_switch_time(local_player->Weapon_switch_time);
		player_snap->set_weapon_slot(local_player->Weapon_slot);
		player_snap->set_weapon_switch(local_player->Weapon_switch);

	

		/* need to do jump, crouch, fire, fire_release, fire_hold still*/
		if (fire_set)
		{
			player_snap->set_fire(true);
		}

		if (fire_hold)
		{
			player_snap->set_fire_hold(true);
			player_snap->set_fire_hold_time(fire_hold_time);
		}

		if (fire_release)
		{
			player_snap->set_fire_release_time(fire_release_time);
			player_snap->set_fire_release(true);
		}

		char* playersnap_packet = new char[PlayerSnapPacket.ByteSize()];
		ZeroMemory(playersnap_packet, PlayerSnapPacket.ByteSize());
		
		PlayerSnapPacket.SerializeToArray(playersnap_packet, PlayerSnapPacket.ByteSize());

		struct sockaddr_in send_to;
		send_to.sin_family = AF_INET;
		send_to.sin_port = htons(port);
		inet_pton(AF_INET, server_ip, &send_to.sin_addr.s_addr);


		sendto(serverSock, playersnap_packet, PlayerSnapPacket.ByteSize(), 0, (LPSOCKADDR)&send_to, sizeof(send_to));

		playersnap_pack_sequence++;
	}

}

/* Only the host should ever be doing this */
void T4Network::ProcessPlayerSnap(const PlayerSnap &pPlayerSnap,u_long pIP, u_short pPort)
{
	int player_index = 0;

	NetworkPlayer *pnet_player = NULL;

	for (NetworkPlayer* net_player : netplayers)
	{
		if (net_player->port == pPort && net_player->ipaddr == pIP)
		{
			pnet_player = net_player;
			player_index = net_player->index;
			break;
		}
	}


	/* This should make sure playersnapshots are never read out of order, and that we don't get duplicates of the same data */
	if (pnet_player->last_packet_seq != 0 && pnet_player->last_packet_seq >= pPlayerSnap.packet_sequence())
	{
		return;
	}
	else 
	{
		pnet_player->last_packet_seq = pPlayerSnap.packet_sequence();
	}

	if (player_index == 0)
	{
		printf("ProcessPlayerSnap(): Player not found\r\n");
		return;
	}

	DMPlayer* pPlayer = netEngine.GetDMPlayer(player_index);
	if (pPlayer)
	{
		pPlayer->ViewX = pPlayerSnap.viewx();
		pPlayer->ViewY = pPlayerSnap.viewy();
		
		pPlayer->POS.x = pPlayerSnap.x();
		pPlayer->POS.y = pPlayerSnap.y();
		pPlayer->POS.z = pPlayerSnap.z();

		pPlayer->Weapon_switch_time = pPlayerSnap.weapon_switch_time();

		if (pPlayer->Weapon_slot != pPlayerSnap.weapon_slot())
			SwitchWeapon(&pPlayer->pWeapon, (pPlayerSnap.weapon_slot()) + 1);

		if (pPlayerSnap.walk_backward())
			pPlayer->Walk_backward = 1.0f;
		else
			pPlayer->Walk_backward = 0.0f;

		if (pPlayerSnap.walk_forward())
			pPlayer->Walk_forward = 1.0f;
		else
			pPlayer->Walk_forward = 0.0f;

		if (pPlayerSnap.walk_left())
			pPlayer->Walk_left = 1.0f;
		else
			pPlayer->Walk_left = 0.0f;

		if (pPlayerSnap.walk_right())
			pPlayer->Walk_right = 1.0f;
		else
			pPlayer->Walk_right = 0.0f;

		if (pPlayerSnap.crouch())
			pPlayer->crouch(0, 1.0f);
		else
			netEngine.UnCrouch(pPlayer);

		if (pPlayerSnap.jump())
			pPlayer->jump(0, 1.0f);
		
		if (pPlayerSnap.fire())
		{
			//printf("Player Fired\r\n");
			pPlayer->fire_weapon(0, 0);
			pnet_player->fire_set = true;
		}
	
		if (pPlayerSnap.fire_hold())
		{
			//printf("Player is holding fire\r\n");
			pPlayer->fire_held(pPlayerSnap.fire_hold_time(), 0);
			pnet_player->fire_hold = true;
			pnet_player->fire_hold_time = pPlayerSnap.fire_hold_time();
		
		}

		if (pPlayerSnap.fire_release())
		{
			//printf("Player released fire\r\n");
			pPlayer->fire_release(pPlayerSnap.fire_release_time());
			pnet_player->fire_release = true;
			pnet_player->fire_release_time = pPlayerSnap.fire_release_time();
		}
	

	}
	else
	{
		printf("ProcessPlayerSnap(): Could not get a valid player for the index: %i\r\n", player_index);
	}


}


void T4Network::ProcessMessage()
{
	int clientLen;
	FD_SET set;
	timeval timeVal;

	FD_ZERO(&set);
	FD_SET(serverSock, &set);

	timeVal.tv_sec = 0;
	timeVal.tv_usec = 0;

	int result = select(FD_SETSIZE, &set, NULL, NULL, &timeVal);

	if (result == SOCKET_ERROR)
	{
		printf("select error\r\n");
		this->Destroy();
		return;
	}

	char buf[800];
	ZeroMemory(buf, 800);

	clientLen = sizeof(clientAddr);

	while(1)
	{

		int recvlen = recvfrom(serverSock, buf, sizeof(buf), 0, (LPSOCKADDR)&clientAddr, &clientLen);

		if (recvlen == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK)
		{
			break;
		}

		char ipbuf[INET_ADDRSTRLEN];

		Packet IncomingPak;
		if (IncomingPak.ParseFromArray(buf, recvlen) && IncomingPak.Type_IsValid(IncomingPak.type()))
		{
			switch (IncomingPak.type())
			{
				case Packet_Type_client_connect:

					if (server)
					{
						if (AddPlayer(clientAddr.sin_addr.s_addr, clientAddr.sin_port))
						{
							printf("Client connected from %s:%d\r\n", inet_ntop(AF_INET, &clientAddr.sin_addr, ipbuf, sizeof(ipbuf)), ntohs(clientAddr.sin_port));
						}
						else
						{
							printf("Client connected from %s:%d\r\n - was already connected!\r\n", inet_ntop(AF_INET, &clientAddr.sin_addr, ipbuf, sizeof(ipbuf)), ntohs(clientAddr.sin_port));
						}
					}
					else 
					{
						if (IncomingPak.has_connect_ack())
						{
							local_index = IncomingPak.connect_ack().index();
							printf("Server acknowledged our connection request our index is now: %i\r\n",local_index);

							connected = true;
						}
					}

				break;

				case Packet_Type_server_snap:
					if(IncomingPak.has_server_snapshot())
					{
						ProcessServerSnap(IncomingPak.server_snapshot());
					}
				break;

				case Packet_Type_client_snap:
					if (IncomingPak.has_player_snapshot())
					{
						ProcessPlayerSnap(IncomingPak.player_snapshot(), clientAddr.sin_addr.s_addr, clientAddr.sin_port);
					}
				break;

				default:
					printf("No packet type matched?\r\n");
				break;
			}
		}
		else
		{
			printf("Received some malformed packet from %s:%d\r\n", inet_ntop(AF_INET, &clientAddr.sin_addr, ipbuf, sizeof(ipbuf)), ntohs(clientAddr.sin_port));
		}
	
		ZeroMemory(buf, 800);
		ZeroMemory(&clientAddr, sizeof(clientAddr));

	}




}

void T4Network::Destroy()
{

}

/* This should only happen to clients! */
void T4Network::ProcessServerSnap(const ServerSnap &pSeverSnap)
{


	if (snappack_sequence != 0 && snappack_sequence >= pSeverSnap.packet_sequence())
	{
		return;
	}
	else 
	{
		snappack_sequence = pSeverSnap.packet_sequence();
	}
	
	/* 
		More code that shouldn't be the way it is, but it'll have to do for the start of things
	
		The way I'd like to handle this is actually make some kind of engine isValid function along with some hooks around whether a level is loaded or not.
		If the level isn't loaded the isValid state would be false, or if the object isn't available we'd return false as well.

	*/
	if (t4engine->pT4Game)
	{
		if (t4engine->pT4Game->pEngineObjects)
		{

			for (const ServerSnap_PlayerData& player : pSeverSnap.player())
			{
				/* Our local player will always be 0 in the game index so we need to provide some translation there */
				bool local_player = false;
				int player_index = player.index();

	
				/* 
					This presents an interesting problem, if someone else joined before us they could have the index of 1, where we want the server to have it... 
					It may be best to avoid using 1 and 0 at all and reserve them for the local player and host for indexes, making the server assigned index 2+ only.
				*/
				
				if (player_index == local_index)
				{
					local_player = true;
					player_index = 0;
				}
			
				if (local_player == false && player_index == 0)
					player_index = local_index;

				bool networked_player = false;
				NetworkPlayer* netplayer = NULL;

				if (!local_player)
				{
					for (NetworkPlayer* check_player : netplayers)
					{
						if (check_player->index == player_index)
						{
							networked_player = true;
							netplayer = check_player;
							break;
						}
					}

					if (!networked_player)
					{
						printf("ProcessServerSnap(): No Network player was found creating one and spawning them! - player_index: %i\r\nProcessServerSnap(): netplayers.size(): %i\r\nPossible Player Indexes:\r\n",player_index,netplayers.size());
				
						NetworkPlayer* nPlayer = new NetworkPlayer;
						nPlayer->index = player_index;
						netplayer = nPlayer;
						netEngine.SpawnPlayer();

						netplayers.push_back(nPlayer);
					}

				}

				bool player_valid = false;

	
				/* Use the player's index to grab the pointer from the in-game array for their BlendedCamera object. */
				BlendedCamera* player_camera = t4engine->pT4Game->pEngineObjects->pCameraArray[player_index];
				DMPlayer *pDMPlayer = NULL;

				if (player_camera) // be sure the camera pointer is valid
				{
				
					if (player_camera->pActor)
					{
						if (player_camera->pActor->pDMPlayer)
						{
							pDMPlayer = player_camera->pActor->pDMPlayer;
							player_valid = true;
						}
					}
					else
					{
							/* If we have to do things this way our player may be dead.... */
							player_valid = false;
							pDMPlayer = (DMPlayer*)player_camera->pPlayer;
					}
				
				}

				//If our player is not valid we do not want to deal with any of their data except for a respawn!
				if (!player_valid)
				{
					if (player.fire())
					{
						if (pDMPlayer)
						{
							pDMPlayer->fire_weapon(0, 0); // this should force a respawn causing the player to be valid in the next frame.

							if (local_player)
							{
								fire_set = false;
								fire_hold = false;
								fire_release = false;
							}

						}
					}
				
				}
				else 
				{
					//If our player is valid lets actually update all their data.
					pDMPlayer->pHealth->Max = player.max_health();

					if (player.current_health() <= 0.0f)
					{
						char* DamagePtr = new char[500];
						ZeroMemory(DamagePtr, 500);
						*(float*)DamagePtr = 1.0f;
						pDMPlayer->pHealth->Current = player.current_health();

						pDMPlayer->KillPlayer(0, player.death_type(), DamagePtr);

						delete[] DamagePtr;
						break;
					}
					else 
					{
						pDMPlayer->pHealth->Current = player.current_health();
					}

					/* Process the Weapon Wheel first */
					if (player.has_weapons()) // does the packet have a weapon wheel?
					{
						if (pDMPlayer->pWeaponWheel) // make sure weapon wheel pointer is valid.
						{

							/* We can skip flamethrower, gravity gun,  bow and tekbow these are not used in traditional multiplayer yet */

							WeaponWheel *weapon_wheel = pDMPlayer->pWeaponWheel;
							ServerSnap_PlayerData_WeaponWheel  nweapon_wheel = player.weapons();
							
							/* Spike Grenade */
							weapon_wheel->bHas_SpikeGrenade = nweapon_wheel.bhas_spikegrenade();
							weapon_wheel->bHas_SpikeGrenade2 = nweapon_wheel.bhas_spikegrenade();

							weapon_wheel->SpikeGrenade_Ammo = nweapon_wheel.spikegrenade_ammo();
							if(nweapon_wheel.spikegrenade_ammo() > 0)
								weapon_wheel->bSpikeGrenade_Has_Ammo = 1;

							/* Pistol */
							weapon_wheel->bHas_Pistol = nweapon_wheel.bhas_pistol();
							weapon_wheel->bHas_Pistol2 = nweapon_wheel.bhas_pistol();

							weapon_wheel->Pistol_Ammo = nweapon_wheel.pistol_ammo();
							if (nweapon_wheel.pistol_ammo() > 0)
								weapon_wheel->bPistol_Has_Ammo = 1;


							/* ShotGun */
							weapon_wheel->bHas_ShotGun = nweapon_wheel.bhas_shotgun();
							weapon_wheel->bHas_ShotGun2 = nweapon_wheel.bhas_shotgun();

							weapon_wheel->ShotGun_Ammo = nweapon_wheel.shotgun_ammo();

							if (nweapon_wheel.shotgun_ammo() > 0)
								weapon_wheel->bShotGun_Has_Ammo1 = 1;
							

							/* Fleechete also is a MiniGun and the MiniGun has seperate ammo */
							weapon_wheel->bHas_Fleechete = nweapon_wheel.bhas_flecheete();
							weapon_wheel->bHas_Fleechete2 = nweapon_wheel.bhas_flecheete();

							weapon_wheel->Fleechete_Ammo = nweapon_wheel.fleechete_ammo();

							if (nweapon_wheel.fleechete_ammo() > 0)
								weapon_wheel->bFleechete_Has_Ammo = 1;

							weapon_wheel->MiniGun_Ammo = nweapon_wheel.minigun_ammo();

							if (nweapon_wheel.minigun_ammo() > 0)
								weapon_wheel->bMiniGun_Has_Ammo = 1;

							/* Rocket Launcher, I know of two modes.. not sure about the third. */
							weapon_wheel->bHas_RocketLauncher = nweapon_wheel.bhas_rocketlauncher();
							weapon_wheel->bHas_RocketLauncher2 = nweapon_wheel.bhas_rocketlauncher();

							weapon_wheel->RocketLauncher_Ammo = nweapon_wheel.rocket_ammo1();
							weapon_wheel->RocketLauncher_Ammo2 = nweapon_wheel.rocket_ammo2();
							weapon_wheel->RocketLauncher_Ammo3 = nweapon_wheel.rocket_ammo3();

							if (nweapon_wheel.rocket_ammo1() > 0)
								weapon_wheel->bRocketLauncher_Has_Ammo = 1;

							if (nweapon_wheel.rocket_ammo2() > 0)
								weapon_wheel->bRocketLauncher_Has_Ammo1 = 1;

							if (nweapon_wheel.rocket_ammo3() > 0)
								weapon_wheel->bRocketLauncher_Has_Ammo2 = 1;


							/* Plasma cannon, I know it has two modes.. I dunno about the third but we're updating it anyway. */
							weapon_wheel->bHas_PlasmaCannon = nweapon_wheel.bhas_plasmacannon();
							weapon_wheel->bHas_PlasmaCannon2 = nweapon_wheel.bhas_plasmacannon();

							weapon_wheel->PlasmaCannon_Ammo = nweapon_wheel.plasma_ammo1();
							weapon_wheel->PlasmaCannon_Ammo2 = nweapon_wheel.plasma_ammo2();
							weapon_wheel->PlasmaCannon_Ammo3 = nweapon_wheel.plasma_ammo3();

							if (nweapon_wheel.plasma_ammo1() > 0)
								weapon_wheel->bPlasmaCannon_Has_Ammo = 1;

							if (nweapon_wheel.plasma_ammo2() > 0)
								weapon_wheel->bPlasmaCannon_Has_Ammo2 = 1;

							if (nweapon_wheel.plasma_ammo3() > 0)
								weapon_wheel->bPlasmaCannon_Has_Ammo3 = 1;

							/* SpiderMine - Disabled we're not ready to sync this data yet... */
							weapon_wheel->bHas_SpiderMine = 0; 
							weapon_wheel->bHas_SpiderMine2 = 0;
							weapon_wheel->SpiderMine_Ammo = 0;
							weapon_wheel->SpiderMine_Ammo2 = 0;
							weapon_wheel->SpiderMine_Ammo3 = 0;


							/* DarkMatter cube, it may have a second option? */
							weapon_wheel->bHas_DarkMatterCube = nweapon_wheel.bhas_darkmatter();
							weapon_wheel->bHas_DarkMatterCube2 = nweapon_wheel.bhas_darkmatter();

							weapon_wheel->DarkMatterCube_Ammo = nweapon_wheel.darkmatter_ammo();
							
							if (nweapon_wheel.darkmatter_ammo() > 0)
								weapon_wheel->bDarkMatterCube_Has_Ammo = 1;

							/* CrossBow */
							weapon_wheel->bHas_CrossBow = nweapon_wheel.bhas_crossbow();
							weapon_wheel->bHas_CrossBow2 = nweapon_wheel.bhas_crossbow();

							weapon_wheel->CrossBow_Normal_Ammo = nweapon_wheel.crossbow_normal_ammo();
							weapon_wheel->CrossBow_Explosive_Ammo = nweapon_wheel.crossbow_explosive_ammo();
							weapon_wheel->CrossBow_Poison_Ammo = nweapon_wheel.crossbow_poison_ammo();

							if (nweapon_wheel.crossbow_normal_ammo() > 0)
								weapon_wheel->bCrossBow_Has_Normal = 1;

							if (nweapon_wheel.crossbow_explosive_ammo() > 0)
								weapon_wheel->bCrossBow_Has_Explosive = 1;

							if (nweapon_wheel.crossbow_poison_ammo() > 0)
								weapon_wheel->bCrossBow_Has_Poison = 1;

						}
					}

					/* Process Player Data*/

					/* This could be important to have before position and walk updates as it affects the speed of the player*/
					
					if (player.crouch())
						pDMPlayer->crouch(0, 1.0f);
					else // should probably be sure they are actually crouched before doing this as it could cause other actions to fail/cancel
						netEngine.UnCrouch(pDMPlayer);
					
					if (!local_player)
					{

						/* View Angles*/
						pDMPlayer->ViewX = player.viewx();
						pDMPlayer->ViewY = player.viewy();

						/* Player Position */

						pDMPlayer->POS.x = player.x();
						pDMPlayer->POS.y = player.y();
						pDMPlayer->POS.z = player.z();

						/* Player Movement - we use these to enable actual walk animation instead of just sliding. */
						if (player.walk_backward())
							pDMPlayer->Walk_backward = 1.0f;
						else
							pDMPlayer->Walk_backward = 0.0f;

						if (player.walk_forward())
							pDMPlayer->Walk_forward = 1.0f;
						else
							pDMPlayer->Walk_forward = 0.0f;

						if (player.walk_left())
							pDMPlayer->Walk_left = 1.0f;
						else
							pDMPlayer->Walk_left = 0.0f;

						if (player.walk_right())
							pDMPlayer->Walk_right = 1.0f;
						else
							pDMPlayer->Walk_right = 0.0f;

						/* Did they jump?, also need to get an idea of what these floats actually do and if they need to be synced. */
						if (player.jump())
							pDMPlayer->jump(0, 0.1f); // not sure how adjusting position just after doing this will affect it, hopefully it just plays jump animation/sounds and such and syncs to the same position we'd expect.

					
					}

					/* 
						Weapon Switch  - Important to do this BEFORE firing as they could have changed weapons!, be sure to update weapon slot first so we switch appropriately
						Should really find a better way to update the weapon being held this is too inacurate, there's a high chance for desync.
					*/

					pDMPlayer->Weapon_switch_time = player.weapon_switch_time(); // how long to wait before performing the switch

					if (local_player && player.weapon_slot() != pDMPlayer->Weapon_slot)
					{
						
						if (weapon_switch_attempts == 60)
						{
							SwitchWeapon(&pDMPlayer->pWeapon, (player.weapon_slot()) + 1);
							weapon_switch_attempts = 0;
						}

						weapon_switch_attempts++;

					}

					if (player.weapon_slot() != pDMPlayer->Weapon_slot && !local_player)
						SwitchWeapon(&pDMPlayer->pWeapon, (player.weapon_slot()) + 1);


					/* Firing Checks  - important to do this AFTER position and other actions */
					if (player.fire())
					{
						if(!local_player)
							pDMPlayer->fire_weapon(0, 0); // again have no idea what the params are for, should determine if they need to be synced.
					}

					if (player.fire_hold())
					{
						if(!local_player)
							pDMPlayer->fire_held(player.fire_hold_time(), 0); // second param isn't synced.
					}
					
					if (player.fire_release())
					{

						if(!local_player)
							pDMPlayer->fire_release(player.fire_release_time());

						if (local_player)
						{
							fire_release = false;
							fire_set = false;
							fire_hold = false;
						}
					}

					

				}
			

				
			}


		}
	}
}


bool T4Network::AddPlayer(u_long ip, u_short client_port)
{
	printf("Attempting to AddPlayer\r\n");

	for (NetworkPlayer* check_player : netplayers)
	{
		if (check_player->ipaddr == ip && check_player->port == client_port)
		{
			/* Be sure we resend an Ack, if they dropped the packet they wouldn't have gotten one and it could be why they're trying to connect again */
			Packet ConnectAckPak;
			ConnectAckPak.set_type(Packet_Type_client_connect);

			ConnectAck *Ack = ConnectAckPak.mutable_connect_ack();
			Ack->set_index(check_player->index);

			char * AckPak = new char[ConnectAckPak.ByteSize()];
			ZeroMemory(AckPak, ConnectAckPak.ByteSize());

			ConnectAckPak.SerializeToArray(AckPak, ConnectAckPak.ByteSize());
	
			sockaddr_in PlayerAddr;

			PlayerAddr.sin_family = AF_INET;
			PlayerAddr.sin_port = client_port;
			PlayerAddr.sin_addr.s_addr = ip;

			int sendlen = sendto(serverSock, AckPak, ConnectAckPak.ByteSize(), 0, (SOCKADDR*)&PlayerAddr, sizeof(PlayerAddr));

			if (sendlen == SOCKET_ERROR)
				printf("WSAError on Send: %08X\r\n", WSAGetLastError());

			char ipbuf[INET_ADDRSTRLEN];
			printf("Player already connected, re-sending ACK to %s:%d - PlayerIndex: %i\r\n", inet_ntop(AF_INET, &PlayerAddr.sin_addr, ipbuf, sizeof(ipbuf)), ntohs(PlayerAddr.sin_port),check_player->index);

			ZeroMemory(&PlayerAddr, sizeof(PlayerAddr));

			return false;
		}
	}

	printf("Adding player\r\n");

	NetworkPlayer* nPlayer = new NetworkPlayer;
	nPlayer->ipaddr = ip;
	nPlayer->port = client_port;
	
	nPlayer->index = netplayers.size()+1;
	netplayers.push_back(nPlayer);
	
	Packet ConnectAckPak;
	ConnectAckPak.set_type(Packet_Type_client_connect);
	
	ConnectAck *Ack = ConnectAckPak.mutable_connect_ack();
	Ack->set_index(nPlayer->index);

	char * AckPak = new char[ConnectAckPak.ByteSize()];
	ZeroMemory(AckPak, ConnectAckPak.ByteSize());

	ConnectAckPak.SerializeToArray(AckPak, ConnectAckPak.ByteSize());

	sockaddr_in PlayerAddr;

	PlayerAddr.sin_family = AF_INET;
	PlayerAddr.sin_port = client_port;
	PlayerAddr.sin_addr.s_addr = ip;

	sendto(serverSock, AckPak, ConnectAckPak.ByteSize(), 0, (SOCKADDR*)&PlayerAddr, sizeof(PlayerAddr));

	nPlayer->PlayerObject = netEngine.SpawnPlayer();


	return true;
}