//----------------------------------------------------------------
// File: patArc.h
// Author: Michel Bierlaire
// Creation: Thu Oct 30 09:40:25 2008
//----------------------------------------------------------------

#ifndef patArc_h
#define patArc_h

#include <iostream>
#include <map>
#include <list>
#include "patCoordinates.h"
#include "patError.h"
#include "patType.h"
#include "patNode.h"
#include "dataStruct.h"
#include "patRoadBase.h"
#include "kml/dom.h"
#include <tr1/unordered_map>
using namespace std::tr1;
using kmldom::PlacemarkPtr;
//#include "patMultiModalPath.h"
struct arc_attributes {
	string type;
	double heading;
	unsigned long priority;
};
class patMultiModalPath;
class patOd;
class patArc: public patRoadBase {
	friend class patPathSampling; //add by Jingmin

	friend class patNode;
	friend class patGpsPoint; //add by Jingmin

	friend class patPathDevelop; //add by Jingmin

	friend class patShortestPathAlgoRange; //add by Jingmin
	friend class patShortestPathTreeRange; //add by Jingmin
	friend class patOd; //add by Jingmin
	friend class patMultiModalPath; //add by Jingmin
	friend class patPathDDR; //add by Jingmin
	friend class patReadSample; //add by Jingmin
	friend class patSample; //add by Jingmin
	friend class patObservation; //add by Jingmin
	friend class patTraveler; //add by Jingmin
	friend class patTripParser; //add by Jingmin
	friend class patTripGraph; //add by Jingmin
	friend class patPathProbaAlgoV2; //add by Jingmin
	friend class patPathProbaAlgoV4; //add by Jingmin
	friend class patArcTransition; //added by Jingmin
	friend class patWriteKML; //added by Jingmin
	friend class patWriteBiogemeInput; //added by Jingmin
	friend class patSimulator; //added by Jingmin
	friend class patMapMatching; //added by Jingmin
	friend class patMapMatchingV2; //added by Jingmin
	friend class patMapMatchingRoute; //added by Jingmin
	friend class patStreetSegment; //added by Jingmin
	friend class patReadObservationFromKML; //added by Jingmin
	friend class patNetworkElements; //add by Jingmin
	friend bool operator<(const patMultiModalPath& aPath,
			const patMultiModalPath& bPath); //add by Jingmin
//	friend ostream& operator<<(ostream& str, patMapMatchingRoute& x);

	friend bool operator==(const patMultiModalPath& aPath,
			const patMultiModalPath& bPath); //add by Jingmin
	friend ostream& operator<<(ostream& str, const patMultiModalPath& x); ///add by Jingmin
	friend class patPath;
	friend class patLinkSubpath;
	friend ostream& operator<<(ostream& str, const patArc& x);

public:
	patArc();
	patArc(unsigned long theId, const patNode* theUpNode,
			const patNode* theDownNode);

	patArc(unsigned long theId, const patNode* theUpNode,
			const patNode* theDownNode, string theName, patError*& err);
	patArc(unsigned long theId, const patNode* theUpNode,
			const patNode* theDownNode, string theName,
			struct arc_attributes theAttr, patError*& err);

	/**
	 @return length of the arc in meters
	 */
//	double getLength() const;
	double computeLength();
	/**
	 @return patTRUE is the arc "follower" is actually consecutive to
	 the current arc
	 */
	bool followedBy(patArc* follower, patError*& err);

	double generalizedCost;
	void calPriority();
	const patNode* getUpNode() const;
	const patNode* getDownNode() const;
	double calHeading();
	vector<const patArc*> getArcList() const;
	virtual vector<const patArc*> getOriginalArcList() const;
	unsigned long getUserId() const;
	double getHeading() const;
	string getName() const;
	int size() const;
	bool isValid() const;
	virtual vector<PlacemarkPtr> getArcKML(string mode) const;

	map<string, double> distanceTo(const patNode* a_node) const;
	virtual double getAttribute(ARC_ATTRIBUTES_TYPES attribute_name) const;
	static string getAttributeTypeString(ARC_ATTRIBUTES_TYPES type_name);
	void setTags(const unordered_map<string, string>& tags);
	void genArcString();
	virtual bool isMotorWay() const;
	virtual bool isPrimaryWay() const;
	virtual bool isSecondaryWay() const;
	virtual bool isTertiaryWay() const;
	virtual bool isTrunk() const;
	virtual double getMotorWayLength() const;

	virtual double getTrunkLength() const;

	virtual double getPrimaryWayLength() const;

	virtual double getSecondaryWayLength() const;

	virtual	double getTertiaryWayLength() const;
	virtual double computeGeneralizedCost(
			const map<ARC_ATTRIBUTES_TYPES, double>& link_coef);
private:
	unordered_map<string, string> m_tags;
	unsigned long m_internal_id;
	struct arc_attributes m_attributes;
protected:
	double frozenGeneralizedCost;
	unsigned long m_user_id;
	const patNode* m_up_node;
	const patNode* m_down_node;
	string m_name;
	unsigned long m_way_id;
	list<patCoordinates> m_polyline;
};

#endif
