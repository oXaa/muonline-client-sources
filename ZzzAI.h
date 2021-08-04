// ĳ���� ���ϸ��̼� ������ ����
int CalcAngle(float PositionX,float PositionY,float TargetX,float TargetY);
float CreateAngle(float x1,float y1,float x2,float y2);
int TurnAngle(int iTheta, int iHeading, int maxTURN);
float TurnAngle2(float angle,float a,float d);
float FarAngle(float angle1,float angle2,bool abs=true);
float MoveHumming(vec3_t Position,vec3_t Angle,vec3_t TargetPosition,float Turn);
void  MovePosition(vec3_t Position,vec3_t Angle,vec3_t Speed);
BYTE  CalcTargetPos ( float x, float y, int Tx, int Ty );
void  Alpha(OBJECT *o);
void MoveBoid(OBJECT *o,int i,OBJECT *Boids,int MAX);
void PushObject(vec3_t PushPosition,vec3_t Position,float Power,vec3_t Angle);
bool CollisionCharacters(CHARACTER *Hero);
bool CollisionObjects(CHARACTER *Hero);

#ifdef CSK_FIX_ANIMATION_BLENDING
void SetAction(OBJECT *o,int Action, bool bBlending=true);
#else // CSK_FIX_ANIMATION_BLENDING 
void SetAction(OBJECT *o,int Action);
#endif // CSK_FIX_ANIMATION_BLENDING

bool TestDistance(CHARACTER *c,vec3_t TargetPosition,float Range);

void LookAtTarget(OBJECT *o,CHARACTER *tc);
void MoveHead(CHARACTER *c);
void Damage(vec3_t soPosition,CHARACTER *tc,float AttackRange,int AttackPoint,bool Hit);
int  CalculateAttackPoint(CHARACTER *sc,CHARACTER *tc);
void AttackCharacter(CHARACTER *sc,CHARACTER *tc,float AttackRange,int AttackPoint,bool Success=true);
void AttackObject(int Type,vec3_t Position,CHARACTER *Owner);


// ��ã�� ���� �Լ�
bool PathFinding(int sx,int sy,int tx,int ty,PATH_t *a);
bool MovePath(CHARACTER *c,bool Turn=true);
void InitPath();
#ifdef YDG_ADD_DOPPELGANGER_MONSTER
bool PathFinding2(int sx,int sy,int tx,int ty,PATH_t *a, float fDistance = 0.0f, int iDefaultWall = TW_CHARACTER);
#else	// YDG_ADD_DOPPELGANGER_MONSTER
bool PathFinding2(int sx,int sy,int tx,int ty,PATH_t *a, float fDistance = 0.0f);
#endif	// YDG_ADD_DOPPELGANGER_MONSTER



//^ �渱 ��ų ����
void SetAction_Fenrir_Skill(CHARACTER* c, OBJECT* o);
void SetAction_Fenrir_Damage(CHARACTER* c, OBJECT* o);
void SetAction_Fenrir_Run(CHARACTER* c, OBJECT* o);
void SetAction_Fenrir_Walk(CHARACTER* c, OBJECT* o);
#ifdef PBG_ADD_NEWCHAR_MONK_ANI
bool IsAliceRideAction_UniDino(unsigned short byAction);
bool IsAliceRideAction_Fenrir(unsigned short byAction);
#else //PBG_ADD_NEWCHAR_MONK_ANI
bool IsAliceRideAction_UniDino(BYTE byAction);
bool IsAliceRideAction_Fenrir(BYTE byAction);
#endif //PBG_ADD_NEWCHAR_MONK_ANI
