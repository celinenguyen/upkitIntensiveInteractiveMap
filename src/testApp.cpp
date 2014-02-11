#include "testApp.h"
#include <iostream>
#include <fstream>

struct hotel {
    string hotelName; // 1
    int stars; // 2
    int price; // 3
    string cityName; // 4
    string countryName; // 7
    float latitude; // 12
    float longitude; // 13
};

int hotelNameCol = 1;
int starsCol = 2;
int priceCol = 3;
int cityNameCol = 4;
int countryNameCol = 7;
int latitudeCol = 12;
int longitudeCol = 13;

int hotelCount = 0;

bool hotelTypeLayer = true;
string hotelTypeName = "Hotel";
int hotelTypeCount = 0;

vector<hotel> hotels;

//--------------------------------------------------------------

//ofVec3f testApp::makeHotelMeshPoint(hotel h) {
//    
//}

void testApp::setup(){
    
    // GUI things
    gui = new ofxUICanvas();
    
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent);
    gui->loadSettings("settings.xml");
    
    // Hotel type terms
    vector<string> hotelType;
    gui->addLabel("Hotel Type Terms", OFX_UI_FONT_MEDIUM);
    hotelType.push_back("Apartment");
    hotelType.push_back("Auberge");
    hotelType.push_back("Bed & Breakfast");
    hotelType.push_back("Camp");
    hotelType.push_back("Casa");
    hotelType.push_back("Castle");
    hotelType.push_back("Chalet");
    hotelType.push_back("Club");
    hotelType.push_back("Guesthouse");
    hotelType.push_back("House");
    hotelType.push_back("Hostel");
    hotelType.push_back("Hotel");
    hotelType.push_back("Inn");
    hotelType.push_back("Lodge");
    hotelType.push_back("Maison");
    hotelType.push_back("Motel");
    hotelType.push_back("Palace");
    hotelType.push_back("Residence");
    hotelType.push_back("Resort");
    hotelType.push_back("Retreat");
    hotelType.push_back("Suites");
    hotelType.push_back("Villa");
    ofxUIRadio *typeRadio = gui->addRadio("VR", hotelType, OFX_UI_ORIENTATION_VERTICAL);
    typeRadio->activateToggle("Hotel");
    
//    // Hotel type terms
//    vector<string> hotelThings;
//    gui->addLabel("Hotel Things Terms", OFX_UI_FONT_MEDIUM);
//    
//    // Hotel type terms
//    vector<string> hotelAmenities;
//    gui->addLabel("Hotel Amenities Terms", OFX_UI_FONT_MEDIUM);
//    hotelAmenities.push_back("Golf");
//    hotelAmenities.push_back("Restaurant");
//    hotelAmenities.push_back("Spa");
    
    gui->autoSizeToFitWidgets();
    
    // CSV things
    csv.loadFile(ofToDataPath("hotelsbase.csv"), "~");
    
    int hotelEntries = csv.numRows;
    int hotelFields = csv.data[0].size();
    float mapLatitude, mapLongitude, mapZ;
    
    mesh.setMode(OF_PRIMITIVE_POINTS);
    hotelTypeMesh.setMode(OF_PRIMITIVE_POINTS);
	
	for (int i = 0; i < hotelEntries; i++) {
        string hotelName = csv.getString(i, hotelNameCol);
        int stars = csv.getInt(i, starsCol);
        int price = csv.getInt(i, priceCol);
        string cityName = csv.getString(i, cityNameCol);
        string countryName = csv.getString(i, countryNameCol);
        float latitude = csv.getFloat(i, latitudeCol);
        float longitude = csv.getFloat(i, longitudeCol);
        
        // put in struct
        hotel currentHotel = {
            hotelName,
            stars,
            price,
            cityName,
            countryName,
            latitude,
            longitude,
        };
        hotels.push_back(currentHotel);
        
        // map coordinates to scale
        mapLatitude = ofMap(latitude, 90, -90, 0, appHeight);
        mapLongitude = ofMap(longitude, -180, 180, 50, appWidth - 50);
        mapZ = stars;
        
        // add to mesh
        ofVec3f currentHotelPoint(mapLongitude, mapLatitude, mapZ);
        mesh.addVertex(currentHotelPoint);
        
        hotelCount++;

//      cout << hotelName << endl;
    }

}

//--------------------------------------------------------------
void testApp::update(){
    if (hotelTypeLayer) {
        hotelTypeMesh.clear();
        hotelTypeCount = 0;
        for(std::vector<hotel>::size_type i = 0; i != hotels.size(); i++) {
            hotel h = hotels[i];
            std::size_t found = h.hotelName.find(hotelTypeName);
            if (found != std::string::npos) {
                float mapLatitude = ofMap(h.latitude, 90, -90, 0, appHeight);
                float mapLongitude = ofMap(h.longitude, -180, 180, 50, appWidth - 50);
                float mapZ = h.stars;
                // add to mesh
                ofVec3f currentHotelPoint(mapLongitude, mapLatitude, mapZ);
                hotelTypeMesh.addVertex(currentHotelPoint);
                
                ofColor c(210, 225, 7);
                hotelTypeMesh.addColor(c);
                
                hotelTypeCount++;
            }
        }
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofColor centerColor = ofColor(38, 105, 117);
    ofColor edgeColor = ofColor(28, 27, 43);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    easyCam.begin();
    easyCam.setScale(1, -1, 1);
    ofPushMatrix();
    ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
    mesh.draw();
    if (hotelTypeLayer) {
        hotelTypeMesh.draw();
    }
    ofPopMatrix();
    easyCam.end();

    if (hotelTypeLayer) {
        string typeStatistics = ofToString(hotelTypeCount) + " of " + ofToString(hotelCount);
        float typePercentage = ((float) hotelTypeCount / hotelCount) * 100;
        string typeStatistics2 = ofToString(ofToString(typePercentage) + "%");
        ofDrawBitmapString(typeStatistics, 600, 700);
        ofDrawBitmapString(typeStatistics2, 600, 715);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key)
    {
        case '0':
        {
            easyCam.reset();
        }
            break;
        case 'g':
        {
            gui->toggleVisible();
        }
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void testApp::exit()
{
    gui->saveSettings("settings.xml");
    delete gui;
    
}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    int on = 1;
    
    if (kind == OFX_UI_WIDGET_TOGGLE) {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        cout << name << "\t value: " << toggle->getValue() << endl;
        hotelTypeLayer = true;
        hotelTypeName = name;
    }
}
