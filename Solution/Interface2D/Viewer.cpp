#include "Viewer.h"
#include "Framework.h"
#include "App.h"
#include "Powerplant.h"
#include "Chargers.h"
#include "Charger.h"
#include "Bases.h"
#include "Base.h"
#include "Bulletin.h"
#include "Bulletins.h"
#include "Refinery.h"
#include "Refineries.h"
#include "GoldMines.h"
#include "GoldMine.h"
#include "Forests.h"
#include "Forest.h"
#include "Miners.h"
#include "Miner.h"
#include "Pioneers.h"
#include "Pioneer.h"
#include "mathmatics.h"
#include "Map.h"
#include "Line.h"
#include "Packet.h"
#include "Enemies.h"
#include "Enemy.h"
#include "Guardians.h"
#include "Guardian.h"
#include "Ground.h"
#include "GroundChip.h"
#include "Coord.h"
#include "Chip.h"
#include "Ratio.h"
#include "Mouse.h"
#include "Drawer.h"
#include <assert.h>

static const int POWERPLANT_OFFSET_X = -32;
static const int CHARGER_OFFSET_X = -32;
static const int BASE_OFFSET_X = -32;
static const int REFINERY_OFFSET_X = -32;
static const int BULLETIN_OFFSET_X = -32;
static const int PACKET_OFFSET_X = -24;
static const int PACKET_OFFSET_Y = -24;
static const int CHIP_SIZE = 32;

enum RES {
	RES_NONE,
	RES_POWERPLANT, 
	RES_CHARGER,    
	RES_REFINERY,    
	RES_BASE,    
	RES_BULLETIN,
	RES_GOLD_MINE,
	RES_FORESTS,
	RES_MINER,
	RES_PIONEER,
	RES_ENEMY,
	RES_GUARDIAN,
	RES_LINE_NORMAL,
	RES_LINE_CIRCUIT,
	RES_LINE_GUIDEPOINT,
	RES_LINE_DELETE,
	RES_PACKET,
	RES_GROUND,
	RES_PLAIN,
	RES_RIVER,
	RES_MOUNTAIN,
	RES_DESERT,
	RES_TREE,
	RES_FLOWER,
	RES_BEAR,
	RES_BEE,
	MAX_RES,
};

ViewerPtr Viewer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Viewer >( fw->getTask( getTag( ) ) );
}

Viewer::Viewer( ) {
	
}

Viewer::~Viewer( ) {
}

void Viewer::initialize( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->load( RES_LINE_NORMAL    , "line_normal.png" );
	drawer->load( RES_LINE_CIRCUIT   , "line_circuit.png" );
	drawer->load( RES_POWERPLANT     , "powerplant.png" );
	drawer->load( RES_CHARGER        , "charger.png" );
	drawer->load( RES_REFINERY       , "refinery.png" );
	drawer->load( RES_BASE			 , "base.png" );
	drawer->load( RES_BULLETIN       , "bulletin.png" );
	drawer->load( RES_LINE_GUIDEPOINT, "line_guide_point.png" );
	drawer->load( RES_GROUND         , "ground.png" );
	drawer->load( RES_LINE_DELETE    , "line_delete.png" );
	drawer->load( RES_PACKET		 , "star.png" );
	drawer->load( RES_GOLD_MINE      , "GoldMine.png" );
	drawer->load( RES_MINER			 , "Miner.png" );
	drawer->load( RES_PIONEER		 , "pioneer.png" );
	drawer->load( RES_FORESTS		 , "forest.png" );
	drawer->load( RES_ENEMY			 , "Enemy.png" );
	drawer->load( RES_GUARDIAN		 , "Gaudian.png" );
	drawer->load( RES_PLAIN			 , "Plain.png" );
	drawer->load( RES_RIVER			 , "River.png" );
	drawer->load( RES_MOUNTAIN		 , "Mountain.png" );
	drawer->load( RES_DESERT		 , "Desert.png" );
	drawer->load( RES_TREE		     , "tree.png" );
	drawer->load( RES_FLOWER		 , "flower.png" );
	drawer->load( RES_BEAR			 , "bear.png" );
	drawer->load( RES_BEE			 , "bee.png" );

	_click_left = CLICK_NONE;
	_click_right = CLICK_NONE;
	_count = 0;
}

void Viewer::update( ) {
	updateClick( );

	drawGround( );
	drawPowerplant( );
	drawChargers( );
	drawBases( );
	drawRefineries( );
	drawBulletins( );
	drawGoldMines( );
	drawForests( );
	drawLine( ); // ラインが画面に表示されていないのでここも関係ない
	drawGuidFacility( );
	drawBear( );
	drawBee( );
	drawGuideLine( );
	drawPacket( );
	drawEnemies( );
	drawGuadians( );
	drawMiners( );
	drawPioneers( );

	reflesh( );
}

void Viewer::reflesh(  ) {
	_guide = GUIDE_NONE;
}

Coord Viewer::getClickCoord( ) const {
	return _click_coord;
}

Viewer::CLICK Viewer::getClickLeft( ) const {
	return _click_left;
}

Viewer::CLICK Viewer::getClickRight( ) const{
	return _click_right;
}

void Viewer::updateClick( ) {
	MousePtr mouse = Mouse::getTask( );

	if ( mouse->isHoldLeftButton( ) ) {
		if ( _click_left == CLICK_PUSH ||
			 _click_left == CLICK_HOLD ) {
			_click_left = CLICK_HOLD;
		} else {
			_click_left = CLICK_PUSH;
		}
	} else {
		if ( _click_left == CLICK_RELEASE ||
			 _click_left == CLICK_NONE ) {
			_click_left = CLICK_NONE;
		} else {
			_click_left = CLICK_RELEASE;
		}
	}
	if ( mouse->isHoldRightButton( ) ) {
		if ( _click_right == CLICK_PUSH ||
			 _click_right == CLICK_HOLD ) {
			_click_right = CLICK_HOLD;
		} else {
			_click_right = CLICK_PUSH;
		}
	} else {
		if ( _click_right == CLICK_RELEASE ||
			 _click_right == CLICK_NONE ) {
			_click_right = CLICK_NONE;
		} else {
			_click_right = CLICK_RELEASE;
		}
	}

	Vector pos = mouse->getPos( );
	_click_coord = Coord( ( int )pos.x / CHIP_SIZE, ( int )pos.y / CHIP_SIZE );
}

void Viewer::drawGround( ) const {

	AppPtr app = App::getTask( );
	if( !app ) {
		return;
	}
	DrawerPtr drawer = Drawer::getTask( );
	GroundPtr ground = app->getGround( );

	// 地面
	for ( int i = 0; i < ground->getWidth( ); i++ ) {
		for ( int j = 0; j < ground->getHeight( ); j++ ) {
			RES resource;
			GROUND_CHIP_TYPE chip = ground->getTypeTerrain( i, j );
			switch( chip ) {
			case GROUND_CHIP_TYPE_PLAIN:
					resource = RES_PLAIN;
					break;
			case GROUND_CHIP_TYPE_RIVER:
					resource = RES_RIVER;
					break;
			case GROUND_CHIP_TYPE_MOUNTAIN:
					resource = RES_MOUNTAIN;
					break;
			case GROUND_CHIP_TYPE_DESERT:
					resource = RES_DESERT;
					break;
			}
			Drawer::Sprite sprite( Drawer::Transform( i * CHIP_SIZE, j * CHIP_SIZE ), resource );
			drawer->set( sprite );
		}
	}

	//オブジェクト
	for ( int i = 0; i < ground->getWidth( ); i++ ) {
		for ( int j = 0; j < ground->getHeight( ); j++ ) {
			GROUND_CHIP_TYPE chip = ground->getType( i, j );
			RES resource = RES_NONE;
			switch( chip ) {
				case GROUND_CHIP_TYPE_FLOWER:
					resource = RES_FLOWER;
					break;
				case GROUND_CHIP_TYPE_TREE:
					resource = RES_TREE;
					break;
			}
			if( resource == RES_NONE ) {
				continue;
			}
			Drawer::Sprite sprite( Drawer::Transform( i * CHIP_SIZE - CHIP_SIZE, j * CHIP_SIZE - CHIP_SIZE ), resource );
			drawer->set( sprite );
		}
	}
}

void Viewer::drawBear( ) const {
	AppPtr app = App::getTask( );
	if( !app ) {
		return;
	}

	DrawerPtr drawer = Drawer::getTask( );
	GroundPtr ground = app->getGround( );

	for ( int i = 0; i < ground->getWidth( ); i++ ) {
		for ( int j = 0; j < ground->getHeight( ); j++ ) {
			GROUND_CHIP_TYPE chip = ground->getType( i, j );
			if ( chip != GROUND_CHIP_TYPE_BEAR ) {
				continue;
			}
			Drawer::Sprite sprite( Drawer::Transform( i * CHIP_SIZE - CHIP_SIZE, j * CHIP_SIZE - CHIP_SIZE ), RES_BEAR );
			drawer->set( sprite );
		}
	}
}

void Viewer::drawBee( ) const {
	AppPtr app = App::getTask( );
	if( !app ) {
		return;
	}

	DrawerPtr drawer = Drawer::getTask( );
	GroundPtr ground = app->getGround( );

	for ( int i = 0; i < ground->getWidth( ); i++ ) {
		for ( int j = 0; j < ground->getHeight( ); j++ ) {
			GROUND_CHIP_TYPE chip = ground->getType( i, j );
			if ( chip != GROUND_CHIP_TYPE_BEE ) {
				continue;
			}
			Drawer::Sprite sprite( Drawer::Transform( i * CHIP_SIZE - CHIP_SIZE, j * CHIP_SIZE - CHIP_SIZE ), RES_BEE );
			drawer->set( sprite );
		}
	}
}

void Viewer::drawPowerplant( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	PowerplantConstPtr powerplant = app->getPowerplant( );
	const Coord& coord = powerplant->getCoord( );

	int sx = coord.x * CHIP_SIZE + POWERPLANT_OFFSET_X;
	int sy = coord.y * CHIP_SIZE;
	Drawer::Sprite sprite( Drawer::Transform( sx, sy ), RES_POWERPLANT );
	DrawerPtr drawer = Drawer::getTask( );
	drawer->set( sprite );
}

void Viewer::drawChargers( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	ChargersConstPtr chargers = app->getChargers( );
	const int size = chargers->getSize( );
	for ( int i = 0; i < size; i++ ) {
		ChargerConstPtr charger = std::dynamic_pointer_cast< const Charger >( chargers->get( i ) );
		const Coord& coord = charger->getCoord( );
		int sx = coord.x * CHIP_SIZE + CHARGER_OFFSET_X;
		int sy = coord.y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_CHARGER ) );
	}

}

void Viewer::drawBases( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	BasesConstPtr bases = app->getBases( );
	const int size = bases->getSize( );
	for ( int i = 0; i < size; i++ ) {
		BaseConstPtr base = std::dynamic_pointer_cast< const Base >( bases->get( i ) );
		const Coord& coord = base->getCoord( );
		int sx = coord.x * CHIP_SIZE + BASE_OFFSET_X;
		int sy = coord.y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_BASE ) );
	}
}

void Viewer::drawRefineries( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	RefineriesConstPtr refineries = app->getRefineries( );
	const int size = refineries->getSize( );
	for ( int i = 0; i < size; i++ ) {
		RefineryConstPtr refinery = std::dynamic_pointer_cast< const Refinery >( refineries->get( i ) );
		const Coord& coord = refinery->getCoord( );
		int sx = coord.x * CHIP_SIZE + REFINERY_OFFSET_X;
		int sy = coord.y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_REFINERY ) );
	}
}

void Viewer::drawBulletins( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	BulletinsConstPtr bulletins = app->getBulletins( );
	const int size = bulletins->getSize( );
	for ( int i = 0; i < size; i++ ) {
		BulletinConstPtr bulletin = std::dynamic_pointer_cast< const Bulletin >( bulletins->get( i ) );
		const Coord& coord = bulletin->getCoord( );
		int sx = coord.x * CHIP_SIZE + BULLETIN_OFFSET_X;
		int sy = coord.y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_BULLETIN ) );
	}
}

void Viewer::drawGuidFacility( ) const {
	if ( _guide == GUIDE_NONE ) {
		return;
	}

	int sx = _coord_guid.x * CHIP_SIZE;
	int sy = _coord_guid.y * CHIP_SIZE;
	RES res = RES_NONE;

	switch ( _guide ) {
	case GUIDE_CHARGER:
		sx += CHARGER_OFFSET_X;
		res = RES_CHARGER;
		break;
	case GUIDE_BASE:
		sx += BASE_OFFSET_X;
		res = RES_BASE;
		break;
	case GUIDE_REFINERY:
		sx += REFINERY_OFFSET_X;
		res = RES_REFINERY;
		break;
	case GUIDE_BULLETIN:
		sx += BULLETIN_OFFSET_X;
		res = RES_BULLETIN;
		break;
	}

	DrawerPtr drawer = Drawer::getTask( );
	drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), res, Drawer::BLEND_ALPHA, 0.5  ) );
}

void Viewer::drawLine( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}

	LineConstPtr line = app->getLine( );

	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < COORD_WIDTH; i++ ) {
		for ( int j = 0; j < COORD_HEIGHT; j++ ) {
			Coord coord( i, j );
			const Line::Chip& chip = line->getChip( coord );
			if ( chip.guide ) {
				continue;
			}
			int idx = convLineTypeToIdx( chip.form_dir );
			if ( idx < 0 ) {
				continue;
			}
			int sx = i * CHIP_SIZE;
			int sy = j * CHIP_SIZE;
			int tx = idx % 4 * CHIP_SIZE;
			int ty = idx / 4 * CHIP_SIZE;
			if ( chip.circuit_dir == Line::DIR_NONE ) {
				drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy, tx, ty, CHIP_SIZE, CHIP_SIZE ), RES_LINE_NORMAL ) );
			} else {
				drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy, tx, ty, CHIP_SIZE, CHIP_SIZE ), RES_LINE_CIRCUIT ) );
			}
		}
	}
}

void Viewer::drawGuideLine( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}

	LineConstPtr line = app->getLine( );
	if ( !line->isGuiding( ) ) {
		return;
	}

	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < COORD_WIDTH; i++ ) {
		for ( int j = 0; j < COORD_HEIGHT; j++ ) {
			Coord coord( i, j );
			const Line::Chip& chip = line->getChip( coord );
			if ( !chip.guide ) {
				continue;
			}
			int idx = convLineTypeToIdx( chip.form_dir );
			if ( idx < 0 ) {
				continue;
			}
			int sx = i * CHIP_SIZE;
			int sy = j * CHIP_SIZE;
			int tx = idx % 4 * CHIP_SIZE;
			int ty = idx / 4 * CHIP_SIZE;
			if ( app->isModeDeleteLine( ) ) {
				drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy, tx, ty, CHIP_SIZE, CHIP_SIZE ),
					RES_LINE_DELETE ) );
			} else {
				drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy, tx, ty, CHIP_SIZE, CHIP_SIZE ),
					RES_LINE_NORMAL, Drawer::BLEND_ALPHA, 0.5 ) );
			}
		}
	}

	{
		int sx = _click_coord.x * CHIP_SIZE;
		int sy = _click_coord.y * CHIP_SIZE;
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_LINE_GUIDEPOINT ) );
	}
}

void Viewer::drawPacket( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	DrawerPtr drawer = Drawer::getTask( );
	LineConstPtr line = app->getLine( );
	Ratio ratio = line->getPacketAnimationRatio( );
	for ( int i = 0; i < Line::PACKET_NUM; i++ ) {
		const Line::PACKET& packet = line->getPacket( i );
		if ( packet.waiting ) {
			continue;
		}

		// animation_ratioをつかって描画位置を計算する
		int sx = int ( packet.coord.x * CHIP_SIZE + CHIP_SIZE * 0.5 - 25 );
		int sy = int ( packet.coord.y * CHIP_SIZE + CHIP_SIZE * 0.5 - 25 );
		setPacketAnimation( sx, sy, packet.dir_in, packet.dir_out, ratio );

		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_PACKET ) );
	}
}

void Viewer::setPacketAnimation( int& sx, int& sy, unsigned char dir_in, unsigned char dir_out, Ratio ratio ) const {
	int length = ratio.cal( CHIP_SIZE );
	unsigned char dir = dir_in;
	if ( ratio.isPassedHalf( ) ) {
		dir = dir_out;
	}

	switch ( dir ) {
	case Line::DIR_U___:
		sy += -length + CHIP_SIZE / 2;
		break;
	case Line::DIR__D__:
		sy +=  length - CHIP_SIZE / 2;
		break;
	case Line::DIR___L_:
		sx += -length + CHIP_SIZE / 2;
		break;
	case Line::DIR____R:
		sx +=  length - CHIP_SIZE / 2;
		break;
	default:
		assert( true );
	}
}


unsigned char Viewer::reverseDir( unsigned char start_dir ) const {
	switch ( start_dir ) {
	case Line::DIR_U___:
		return Line::DIR__D__;
		break;
	case Line::DIR__D__:
		return Line::DIR_U___;
		break;
	case Line::DIR___L_:
		return Line::DIR____R;
		break;
	case Line::DIR____R:
		return Line::DIR___L_;
		break;
	default:
		return -1;
		break;
	}
}

void Viewer::setGuidFacility( const Coord& coord, GUIDE guide ) {
	_coord_guid = coord;
	_guide = guide;
}

int Viewer::convLineTypeToIdx( unsigned char dir ) const {
	switch ( dir ) {
	case Line::DIR___LR:
		return 0;
		break;
	case Line::DIR_UD__:
		return 1;
		break;
	case Line::DIR_U__R:
		return 2;
		break;
	case Line::DIR_U_L_:
		return 3;
		break;
	case Line::DIR__D_R:
		return 4;
		break;
	case Line::DIR__DL_:
		return 5;
		break;
	case Line::DIR_U_LR:
		return 6;
		break;
	case Line::DIR__DLR:
		return 7;
		break;
	case Line::DIR_UD_R:
		return 8;
		break;
	case Line::DIR_UDL_:
		return 9;
		break;
	case Line::DIR_UDLR:
		return 10;
		break;
	default:
		return -1;
		break;
	}

}


void Viewer::drawGoldMines( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	GoldMinesPtr gold_mines = app->getGoldMines( );
	const int size = gold_mines->getSize( );
	for ( int i = 0; i < size; i++ ) {
		GoldMinePtr gold_mine = gold_mines->get( i );
		int sx = gold_mine->getCoord( ).x * CHIP_SIZE;
		int sy = gold_mine->getCoord( ).y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_GOLD_MINE ) );
	}
}

void Viewer::drawForests( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	ForestsPtr forests = app->getForests( );
	const int size = forests->getSize( );
	for ( int i = 0; i < size; i++ ) {
		ForestPtr forest = forests->get( i );
		int sx = forest->getCoord( ).x * CHIP_SIZE;
		int sy = forest->getCoord( ).y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_FORESTS ) );
	}
}

void Viewer::drawEnemies( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	EnemiesPtr enemies = app->getEnemies( );
	const int size = enemies->getSize( );
	for ( int i = 0; i < size; i++ ) {
		EnemyPtr enemy = enemies->get( i );
		int sx = enemy->getCoord( ).x * CHIP_SIZE;
		int sy = enemy->getCoord( ).y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_ENEMY ) );
	}
}

void Viewer::drawGuadians( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	GuardiansPtr guardians = app->getGuardians( );
	const int size = guardians->getSize( );
	for ( int i = 0; i < size; i++ ) {
		GuardianPtr guardian = guardians->get( i );
		int sx = guardian->getCoord( ).x * CHIP_SIZE;
		int sy = guardian->getCoord( ).y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_GUARDIAN ) );
	}
}


void Viewer::drawMiners( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	MinersConstPtr miners = app->getMiners( );
	const int size = miners->getSize( );
	for ( int i = 0; i < size; i++ ) {
		MinerConstPtr miner = miners->get( i );
		RatioCoord ratio = miner->getRatioCoord( );
		Coord coord = ratio.getCoord( );
		int sx = coord.x * CHIP_SIZE + ratio.getRatio( ).x.cal( CHIP_SIZE ) - CHIP_SIZE / 2;
		int sy = coord.y * CHIP_SIZE + ratio.getRatio( ).y.cal( CHIP_SIZE ) - CHIP_SIZE / 2;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_MINER ) );
	}
}

void Viewer::drawPioneers( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	PioneersConstPtr pioneers = app->getPioneers( );
	const int size = pioneers->getSize( );
	for ( int i = 0; i < size; i++ ) {
		PioneerConstPtr pioneer = pioneers->get( i );
		RatioCoord ratio = pioneer->getRatioCoord( );
		Coord coord = ratio.getCoord( );
		int sx = coord.x * CHIP_SIZE + ratio.getRatio( ).x.cal( CHIP_SIZE ) - CHIP_SIZE / 2;
		int sy = coord.y * CHIP_SIZE + ratio.getRatio( ).y.cal( CHIP_SIZE ) - CHIP_SIZE / 2;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_PIONEER ) );
	}
}
