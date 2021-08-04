
#ifdef CSK_DEBUG_MAP_PATHFINDING
	#define SHOW_PATH_INFO
	extern bool g_bShowPath;
#endif // CSK_DEBUG_MAP_PATHFINDING

#ifdef _DEBUG
	//#define SAVE_PATH_TIME
#endif

#include <math.h>
#include "BaseCls.h"
#include "./Utilities/Log/ErrorReport.h"

class PATH
{
public:
	PATH();
	~PATH();

	// �ʱ�ȭ
public:
    void SetMapDimensions( int iWidth, int iHeight, WORD *pbyMap);

	// �� ����
private:
	int	m_iWidth, m_iHeight;
	int m_iSize;
	WORD* m_pbyMap;

	// ã�� �� ����
private:
	int m_iNumPath;
	BYTE m_xPath[MAX_COUNT_PATH];
	BYTE m_yPath[MAX_COUNT_PATH];
public:
	int GetPath( void)	{ return ( min( m_iNumPath, MAX_PATH_FIND)); }
	BYTE* GetPathX( void)	{ return ( m_xPath + MAX_COUNT_PATH - m_iNumPath); }
	BYTE* GetPathY( void)	{ return ( m_yPath + MAX_COUNT_PATH - m_iNumPath); }

	// ������ ����
	int GetIndex( int xPos, int yPos)	{ return ( xPos + yPos * m_iWidth); }
	void GetXYPos( int iIndex, int *pxPos, int *pyPos)	{ *pxPos = iIndex % m_iWidth; *pyPos = iIndex / m_iWidth; }
	BOOL CheckXYPos( int xPos, int yPos)	{ return ( xPos >= 0 && yPos >= 0 && xPos < m_iWidth && yPos < m_iHeight);}
	static int s_iDir[8][2];

	// ��ã�� ���� ����
private:
	BYTE *m_pbyClosed;	                // ���ȴ°�? �����°�? ( 0 : ���� ��, 1 : ���� ��)
	int m_iMinClosed, m_iMaxClosed;	    // m_pbyClosed �� �ʱ�ȭ�� ����
	int *m_piCostToStart;		        // ������������ ���
	int *m_pxPrev;		                // �ٷ� ���� ���
	int *m_pyPrev;
	CBTree<int, int> m_btOpenNodes;	    // �˻��غ� �͵��� ����Ʈ ( �ε���, ���� �Ѻ��)

	void Clear( void);
	bool AddClearPos( int iIndex);
	void Init( void);
	int GetNewNodeToTest( void);

	// �� ã��
public:
	bool FindPath(int xStart, int yStart, int xEnd, int yEnd, bool bErrorCheck, int iWall, bool Value, float fDistance = 0.0f);

private:
	void SetEndNodes( bool bErrorCheck, int iWall, int xEnd, int yEnd, float fDistance);
	int CalculateCostToStartAddition( int xDir, int yDir);
	int EstimateCostToGoal( int xStart, int yStart, int xNew, int yNew);
	bool GeneratePath( int xStart, int yStart, int xEnd, int yEnd);

	// ����׿� �Լ�
#ifdef SHOW_PATH_INFO
public:
	BYTE GetClosedStatus( int iIndex)	{ return ( m_pbyClosed[iIndex]); }
#endif // SHOW_PATH_INFO

};


inline PATH::PATH()
{
	m_pbyClosed = NULL;
	m_piCostToStart = NULL;
	m_pxPrev = NULL;
	m_pyPrev = NULL;
}

inline PATH::~PATH()
{
	Clear();
}

inline void PATH::Clear( void)
{
	if ( m_pbyClosed)
	{
		delete [] m_pbyClosed;
		m_pbyClosed = NULL;
	}
	if ( m_piCostToStart)
	{
		delete [] m_piCostToStart;
		m_piCostToStart = NULL;
	}
	if ( m_pxPrev)
	{
		delete [] m_pxPrev;
		m_pxPrev = NULL;
	}
	if ( m_pyPrev)
	{
		delete [] m_pyPrev;
		m_pyPrev = NULL;
	}
	m_iMinClosed = MAX_INT_FORPATH;
	m_iMaxClosed = -1;
}

inline void PATH::SetMapDimensions( int iWidth, int iHeight, WORD* pbyMap)
{
	Clear();

	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_pbyMap = pbyMap;
	m_iSize  = m_iWidth*m_iHeight;

	m_pbyClosed = new BYTE [m_iSize];
	m_piCostToStart = new int [m_iSize];
	m_pxPrev = new int [m_iSize];
	m_pyPrev = new int [m_iSize];
	ZeroMemory( m_pbyClosed, m_iSize* sizeof ( BYTE));
}

inline bool PATH::AddClearPos( int iIndex)
{
	if(iIndex < 0 || iIndex >= m_iSize)
	{
		return false;
	}

	m_iMinClosed = min( iIndex, m_iMinClosed);
	m_iMaxClosed = max( iIndex, m_iMaxClosed);

	return true;
}

inline void PATH::Init( void)
{
	if(MAX_INT_FORPATH == m_iMinClosed)
	{
		return;
	}

	ZeroMemory( &( m_pbyClosed[m_iMinClosed]), ( m_iMaxClosed - m_iMinClosed + 1) * sizeof ( BYTE));
	m_iMinClosed = MAX_INT_FORPATH;
	m_iMaxClosed = -1;
}

inline int PATH::GetNewNodeToTest( void)
{	
	// ���� �˻��� ��带 ���´�.
	CBNode<int, int> *pResult = NULL;
	CBNode<int, int> *pNode = m_btOpenNodes.FindHead();
	while ( pNode)
	{
		pResult = pNode;
		pNode = m_btOpenNodes.GetLeft( pNode);
	}

#if _DEBUG
	if ( !pResult)
	{
		return ( -1);
	}
#endif // _DEBUG

	return ( m_btOpenNodes.RemoveNode( pResult));
}

// bErrorCheck �� false �̸� ���� ������ ����.
inline bool PATH::FindPath( int xStart, int yStart, int xEnd, int yEnd, bool bErrorCheck, int iWall, bool Value, float fDistance)
{	
	Init();

	// 1. �߸��� ȣ�� üũ
	if(xStart == 0 || yStart == 0)
	{
		return false;
	}

	// 2. ������ �� �� �ִ� ������ üũ
	if(0.0f == fDistance)
	{
		int iEndIndex = GetIndex(xEnd, yEnd);
		if(iEndIndex < 0 || iEndIndex >= m_iSize)	//. �ε����� ���� ���̶�� ����!
		{
			return false;
		}
		
		if(Value == true)
		{
			m_pbyMap[iEndIndex] = 0;
		}

		if(bErrorCheck && (iWall <= m_pbyMap[iEndIndex] && (m_pbyMap[GetIndex(xEnd, yEnd)]&TW_ACTION) != TW_ACTION))
		{
			return false;
		}

		m_pbyClosed[iEndIndex] = PATH_END;
		if(!AddClearPos(iEndIndex))
		{
			return false;
		}
	}
	else
	{
		SetEndNodes( bErrorCheck, iWall, xEnd, yEnd, fDistance);
	}

	// �� �� ���� ��� ���� ����� �������� ���� �ϱ� ���� ����
	int iCostToGoalOfNearest = MAX_INT_FORPATH;
	int xNearest = xStart;
	int yNearest = yStart;

	// 3. �������� ����� 0 �� ������ �߰��Ѵ�.
	int iStartIndex = GetIndex( xStart, yStart);
	if (iStartIndex < 0 || iStartIndex >= m_iSize)		//. �ε����� ���� ���̶�� ����!
	{
		return false;
	}

	m_btOpenNodes.Add( iStartIndex, 0);
	m_pbyClosed[iStartIndex] |= PATH_INTESTLIST;
	if(!AddClearPos( iStartIndex))
	{
		return false;
	}

	// 4. �ϳ��� �˻��غ��鼭 �� �ֺ��� �͵��� �˻� ����Ʈ�� �ִ´�.
	int iMaxCount = bErrorCheck ? 500 : 50;
	for(int iCheckCount = iMaxCount; 0 < m_btOpenNodes.GetCount() && iCheckCount > 0; --iCheckCount)
	{
		// a) ���� �˻��� ��ġ ���
		int xTest, yTest;
		int iIndex = GetNewNodeToTest();
		GetXYPos( iIndex, &xTest, &yTest);

		// b) ���� m_piCostToStart ���
		m_piCostToStart[iIndex] = ( iCheckCount == iMaxCount) ? 0 : MAX_INT_FORPATH;
		for ( int i = 0; i < 8; i++)
		{	// �ֺ����� �� ����� ���� ������ �� ������ ����
			int xNear = xTest + s_iDir[i][0];
			int yNear = yTest + s_iDir[i][1];
			if ( !CheckXYPos( xNear, yNear))
			{
				continue;
			}
			int iNearIndex = GetIndex( xNear, yNear);
			if ( PATH_TESTED & m_pbyClosed[iNearIndex])
			{
				// ** CostToStart ��� **
				int iNewCost = m_piCostToStart[iNearIndex] + CalculateCostToStartAddition( s_iDir[i][0], s_iDir[i][1]);
				if ( iNewCost < m_piCostToStart[iIndex])
				{
					m_piCostToStart[iIndex] = iNewCost;
					m_pxPrev[iIndex] = xNear;
					m_pyPrev[iIndex] = yNear;
				}
			}
		}
		m_pbyClosed[iIndex] |= PATH_TESTED;
		// c) ã�� ���
		if ( PATH_END & m_pbyClosed[iIndex])
		{
			m_btOpenNodes.RemoveAll();
			return ( GeneratePath( xStart, yStart, xTest, yTest));
		}
		// d) �ֺ��� 8 ������ �˻� ����Ʈ�� �߰�
#ifdef _VS2008PORTING
		for (int i = 0; i < 8; i++)
#else // _VS2008PORTING
		for ( i = 0; i < 8; i++)
#endif // _VS2008PORTING
		{
			int xNew = xTest + s_iDir[i][0];
			int yNew = yTest + s_iDir[i][1];
			if ( !CheckXYPos( xNew, yNew))
			{
				continue;
			}
			int iNewIndex = GetIndex( xNew, yNew);
            int byMapAttribute = m_pbyMap[iNewIndex];

            if ( (byMapAttribute&TW_ACTION)==TW_ACTION ) byMapAttribute -= TW_ACTION;
            if ( (byMapAttribute&TW_HEIGHT)==TW_HEIGHT ) byMapAttribute -= TW_HEIGHT;
            if ( (byMapAttribute&TW_CAMERA_UP)==TW_CAMERA_UP ) byMapAttribute -= TW_CAMERA_UP;

			if ( !( PATH_INTESTLIST & m_pbyClosed[iNewIndex]) && iWall > byMapAttribute )
			{
				// ** ���� �Ѻ�� ��� **
				int iNewCost = m_piCostToStart[iIndex] + EstimateCostToGoal( xEnd, yEnd, xNew, yNew);
				m_btOpenNodes.Add( iNewIndex, iNewCost);
				m_pbyClosed[iNewIndex] |= PATH_INTESTLIST;
				if(!AddClearPos( iNewIndex))
					return false;
				m_pxPrev[iNewIndex] = xTest;
				m_pyPrev[iNewIndex] = yTest;
			}
		}
		// e) �Ϸ�
		if ( !bErrorCheck)
		{	// ��ó���� ���� �Ǵ� ���, ���� ����� ��ġ���� üũ
			int iCostToGoal = EstimateCostToGoal( xEnd, yEnd, xTest, yTest);
			if ( iCostToGoal < iCostToGoalOfNearest)
			{
				iCostToGoalOfNearest = iCostToGoal;
				xNearest = xTest;
				yNearest = yTest;
			}
		}
	}
	// 5. ����� �������� ����.
	if(!bErrorCheck)
	{
		m_btOpenNodes.RemoveAll();
		return ( GeneratePath( xStart, yStart, xNearest, yNearest));
	}

	// 6. ã�� �� ���� ��� ����
	m_btOpenNodes.RemoveAll();

	return false;
}

inline void PATH::SetEndNodes( bool bErrorCheck, int iWall, int xEnd, int yEnd, float fDistance)
{
	int iDistance = ( int)fDistance;
	for ( int j = -iDistance; j <= iDistance; j++)
	{
		// �� ������ ������ �κ��� ������ ����
		int xRange = iDistance - abs( j);
		for ( int i = -xRange; i <= 0; i++)
		{
			int iEndIndex = GetIndex( xEnd + i, yEnd + j);
			if ( iEndIndex>=0 && iEndIndex<(m_iSize) )
			{
				if ( !( bErrorCheck && iWall <= m_pbyMap[iEndIndex]))
				{
					m_pbyClosed[iEndIndex] = PATH_END;
					AddClearPos( iEndIndex);
				}
			}
            else
            {
        		g_ErrorReport.Write( "�߸��� ��ġ�ε��� : %d \r\n", iEndIndex);
            }
			iEndIndex = GetIndex( xEnd - i, yEnd + j);

            if ( iEndIndex>=0 && iEndIndex<(m_iSize) )
			{
				if ( !( bErrorCheck && iWall <= m_pbyMap[iEndIndex]))
				{
					m_pbyClosed[iEndIndex] = PATH_END;
					AddClearPos( iEndIndex);
				}
			}
            else
            {
        		g_ErrorReport.Write( "�߸��� ��ġ�ε��� : %d \r\n", iEndIndex);
            }
		}
		// �� ������ ������ �Ÿ� ����ؼ� ����
#ifdef _VS2008PORTING
		for ( int i = -iDistance; i < -xRange; i++)
#else // _VS2008PORTING
		for ( i = -iDistance; i < -xRange; i++)
#endif // _VS2008PORTING
		{
#ifdef _VS2008PORTING
			if ( ( float)sqrt( (float)(i * i + j * j)) < fDistance)
#else // _VS2008PORTING
			if ( ( float)sqrt( i * i + j * j) < fDistance)
#endif // _VS2008PORTING
			{
				int iEndIndex = GetIndex( xEnd + i, yEnd + j);
				if ( iEndIndex>=0 && iEndIndex<(m_iSize) )
				{
					if ( !( bErrorCheck && iWall <= m_pbyMap[iEndIndex]))
					{
						m_pbyClosed[iEndIndex] = PATH_END;
						AddClearPos( iEndIndex);
					}
				}
                else
                {
        		    g_ErrorReport.Write( "�߸��� ��ġ�ε��� : %d \r\n", iEndIndex);
                }

                iEndIndex = GetIndex( xEnd - i, yEnd + j);
				if ( iEndIndex>=0 && iEndIndex<(m_iSize) )
				{
					if ( !( bErrorCheck && iWall <= m_pbyMap[iEndIndex]))
					{
						m_pbyClosed[iEndIndex] = PATH_END;
						AddClearPos( iEndIndex);
					}
				}
                else
                {
        		    g_ErrorReport.Write( "�߸��� ��ġ�ε��� : %d \r\n", iEndIndex);
                }
			}
		}
	}
}

inline int PATH::CalculateCostToStartAddition( int xDir, int yDir)
{
	return ( ( xDir == 0 || yDir == 0) ? FACTOR_PATH_DIST : FACTOR_PATH_DIST_DIAG);
}

inline int PATH::EstimateCostToGoal( int xStart, int yStart, int xNew, int yNew)
{
	//�簢+�밢���Ÿ�
	int xDist = abs( xNew - xStart);
	int yDist = abs( yNew - yStart);
	if ( xDist == 1 && yDist == 1)
	{	// ��簡 �밢������ ������ �ʴ� ���� ���� ����
		yDist = 0;
	}

	return ( abs( xDist - yDist) * FACTOR_PATH_DIST + min( xDist, yDist) * FACTOR_PATH_DIST_DIAG + 1) * 3 / 4;
}

inline bool PATH::GeneratePath( int xStart, int yStart, int xEnd, int yEnd)
{
	int xCurrent = xEnd;
	int yCurrent = yEnd;
	for ( m_iNumPath = 0; m_iNumPath < MAX_COUNT_PATH; m_iNumPath++)
	{
		// ã�� ���� ������ �ִ´�.
		m_xPath[( MAX_COUNT_PATH - 1) - m_iNumPath] = xCurrent;
		m_yPath[( MAX_COUNT_PATH - 1) - m_iNumPath] = yCurrent;

		if ( xCurrent == xStart && yCurrent == yStart)
		{
			m_iNumPath++;
			return ( true);
		}

		int iIndex = GetIndex( xCurrent, yCurrent);
		xCurrent = m_pxPrev[iIndex];
		yCurrent = m_pyPrev[iIndex];
	}

	return ( false);
}