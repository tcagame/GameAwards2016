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
#include "mathmatics.h"
#include "Map.h"
#include "Line.h"
#include "Packets.h"
#include "Packet.h"
#include "Coord.h"
#include "Chip.h"
#include "Ratio.h"
#include "Mouse.h"
#include "Drawer.h"

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
	RES_LINE_NORMAL,
	RES_LINE_CIRCUIT,
	RES_LINE_GUIDEPOINT,
	RES_LINE_DELETE,
	RES_PACKET,
	RES_GROUND,
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
	drawLine( ); // ƒ‰ƒCƒ“‚ª‰æ–Ê‚É•\Ž¦‚³‚ê‚Ä‚¢‚È‚¢‚Ì‚Å‚±‚±‚àŠÖŒW‚È‚¢
	drawGuidFacility( );
	drawGuideLine( );
	drawPacket( );

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

void Viewer::drawGround( ) {
	DrawerPtr drawer = Drawer::getTask( );
	for ( int j = 0; j < COORD_HEIGHT; j++ ) {
		for ( int i = j % 2; i < COORD_WIDTH; i += 2 ) {
			Drawer::Sprite sprite( Drawer::Transform( i * CHIP_SIZE - CHIP_SIZE, j * CHIP_SIZE ), RES_GROUND );
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
	Coord coord = powerplant->getCoord( );

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
		Coord coord = charger->getCoord( );
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
		Coord coord = base->getCoord( );
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
		Coord coord = refinery->getCoord( );
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
		Coord coord = bulletin->getCoord( );
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
	const Line::Data data = line->getData( );

	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < COORD_WIDTH; i++ ) {
		for ( int j = 0; j < COORD_HEIGHT; j++ ) {
			Line::Data::Chip chip = data.array[ i + j * COORD_WIDTH ];
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
	const Line::Data data = line->getData( );
	for ( int i = 0; i < COORD_WIDTH; i++ ) {
		for ( int j = 0; j < COORD_HEIGHT; j++ ) {
			Line::Data::Chip chip = data.array[ i + j * COORD_WIDTH ];
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
	PacketsConstPtr packets = app->getPackets( );
	int count = packets->getCount( );
	for ( int i = 0; i < count; i++ ) {
		PacketPtr packet = packets->get( i );
		Coord coord = packet->getCoord( );
		Ratio ratio_x = packet->getRatioX( );
		Ratio ratio_y = packet->getRatioY( );
		int sx = coord.x * CHIP_SIZE + ratio_x.cal( CHIP_SIZE ) + PACKET_OFFSET_X;
		int sy = coord.y * CHIP_SIZE + ratio_y.cal( CHIP_SIZE ) + PACKET_OFFSET_Y;
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_PACKET ) );
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