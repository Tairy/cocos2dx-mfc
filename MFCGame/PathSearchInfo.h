#include "cocos2d.h"
#include "vector"
#include "PathSprite.h"
using namespace std;
USING_NS_CC;
#define MAP_WIDTH 50 //Ҫ��tmx�е�map��
#define MAP_HEIGHT 50
#define PLAYER_COUNT 3
class PathSearchInfo//Ѱ·��(��Ҫ����Ѱ·�Ĳ������߼�)
{
public:
    
    static int m_startX;//��ʼ��
    static int m_startY;
    
    static int m_endX;//������
    static int m_endY;
 
    static CCSize m_mapSize;//��ͼ��С
    static CCSize m_tileSize;//��ͼ�Ŀ��С
    static vector<PathSprite*> m_openList;//�����б�(���������ڽڵ�)
    static PathSprite* m_inspectArray[MAP_WIDTH][MAP_HEIGHT];//ȫ����Ҫ���ĵ�
    static vector<PathSprite*> m_pathList;//·���б�
    static vector<PathSprite*> m_haveInspectList;//�������б�

    static float calculateTwoObjDistance(PathSprite* obj1, PathSprite* obj2)//�������������ľ���
    {
        //        float _offsetX = obj1->m_x - obj2->m_x;
        //        float _offsetY = obj1->m_y - obj2->m_y;
        //        return sqrt( _offsetX * _offsetX + _offsetY * _offsetY);
        
        float _x = abs(obj2->m_x - obj1->m_x);
        float _y = abs(obj2->m_y - obj1->m_y);
        
        return _x + _y;
    }
    static void inspectTheAdjacentNodes(PathSprite* node, PathSprite* adjacent, PathSprite* endNode)//�����ڵĽڵ���뿪�Žڵ���
    {
        if (adjacent)
        {
            float _x = abs(endNode->m_x - adjacent->m_x);
            float _y = abs(endNode->m_y - adjacent->m_y);
            
            float F , G, H1, H2, H3;
            adjacent->m_costToSource = node->m_costToSource + calculateTwoObjDistance(node, adjacent);//����ۼƵ�·��
            G = adjacent->m_costToSource;
            
            //�����㷨, �о�H2����
            H1 = _x + _y;
            H2 = hypot(_x, _y);
            H3 = max(_x, _y);
            
#if 1 //A*�㷨 = Dijkstra�㷨 + �����������
            F = G + H2;
#endif
#if 0//Dijkstra�㷨
            F = G;
#endif
#if 0//�����������
            F = H2;
#endif
            adjacent->m_FValue = F;
            
            adjacent->m_parent = node;//���ø��ڵ�
            adjacent->m_sprite->setColor(ccORANGE);//��Ѱ���Ľڵ���Ϊ��ɫ(������)
            m_haveInspectList.push_back(adjacent);
            node->m_child = adjacent;//�����ӽڵ�

            PathSearchInfo::m_inspectArray[adjacent->m_x][adjacent->m_y] = NULL;//�Ѽ����ĵ�Ӽ���б���ɾ��
            PathSearchInfo::m_openList.push_back(adjacent);//���뿪���б�
        }
    }
    static PathSprite* getMinPathFormOpenList()//�ӿ��Žڵ��л�ȡFֵ��Сֵ�ĵ�
    {
        if (m_openList.size()>0) {
            PathSprite* _sp =* m_openList.begin();
            for (vector<PathSprite*>::iterator iter = m_openList.begin(); iter !=  m_openList.end(); iter++)
            {
                if ((*iter)->m_FValue < _sp->m_FValue)
                {
                    _sp = *iter;
                }
            }
            return _sp;
        }
        else
        {
            return NULL;
        }
        
    }
    static PathSprite* getObjFromInspectArray(int x, int y)//���ݺ�������Ӽ�������л�ȡ��
    {
        if (x >=0 && y >=0 && x < m_mapSize.width && y < m_mapSize.height) {
            return m_inspectArray[x][y];
        }
        return  NULL;
    }
    static bool removeObjFromOpenList( PathSprite* sprite)//�ӿ����б����Ƴ�����
    {
        if (!sprite) {
            return  false;
        }
        for (vector<PathSprite*>::iterator iter = m_openList.begin(); iter !=  m_openList.end(); iter++)
        {
            if (*iter == sprite)
            {
                m_openList.erase(iter);
                return true;
            }
        }
        return false;
        
    }  
};