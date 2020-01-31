#include <iostream>
#include <stack>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

struct Point{  
    //������
    int row;  
    int col;  
    Point(int x,int y){
        this->row=x;
        this->col=y;
    }

    bool operator!=(const Point& rhs){
        if(this->row!=rhs.row||this->col!=rhs.col)
            return true;
        return false;
    }

    bool operator==(const Point& rhs) const{
        if(this->row==rhs.row&&this->col==rhs.col)
            return true;
        return false;
    }
};  



//func:��ȡ����δ�����ʵĽڵ�
//para:mark:����ǣ�point����㣻m���У�n����;endP:�յ�
//ret:�ڽ�δ�����ʵĽ��
Point getAdjacentNotVisitedNode(int** mark,Point point,int m,int n,Point endP){
    Point resP(-1,-1);
    if(point.row-1>=0){
        if(mark[point.row-1][point.col]==0||mark[point.row][point.col]+1<mark[point.row-1][point.col]){//�Ͻڵ���������
            resP.row=point.row-1;
            resP.col=point.col;
            return resP;
        }
    }
    if(point.col+1<n){
        if(mark[point.row][point.col+1]==0||mark[point.row][point.col]+1<mark[point.row][point.col+1]){//�ҽڵ���������
            resP.row=point.row;
            resP.col=point.col+1;
            return resP;
        }
    }
    if(point.row+1<m){
        if(mark[point.row+1][point.col]==0||mark[point.row][point.col]+1<mark[point.row+1][point.col]){//�½ڵ���������
            resP.row=point.row+1;
            resP.col=point.col;
            return resP;
        }
    }
    if(point.col-1>=0){
        if(mark[point.row][point.col-1]==0||mark[point.row][point.col]+1<mark[point.row][point.col-1]){//��ڵ���������
            resP.row=point.row;
            resP.col=point.col-1;
            return resP;
        }
    }
    return resP;
}

//func��������ά�Թ��������·��
//para:maze���Թ���m���У�n���У�startP����ʼ��� endP��������㣻 pointStack��ջ�����·�����;vecPath:������·��
//ret:��
void mazePath(void* maze,int m,int n, Point& startP, Point endP,stack<Point>& pointStack,vector<Point>& vecPath){
    //�����������������Ķ�ά���黹ԭΪָ�����飬��֧���±����
    int** maze2d=new int*[m];
    for(int i=0;i<m;++i){
        maze2d[i]=(int*)maze+i*n;
    }

    if(maze2d[startP.row][startP.col]==-1||maze2d[endP.row][endP.col]==-1)
        return ;                    //�������

    //���������ڵ���ʱ�ǣ���ʾ��㵽������Ȩֵ��Ҳ��¼����㵽��ǰ���·���ĳ���
    int** mark=new int*[m];
    for(int i=0;i<m;++i){
        mark[i]=new int[n];
    }
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            mark[i][j]=*((int*)maze+i*n+j);
        }
    }
    if(startP==endP){//�������յ�
        vecPath.push_back(startP);
        return;
    }

    //����һ���յ���ѱ����ʵ�ǰ����㼯
    vector<Point> visitedEndPointPreNodeVec;

    //�������ջ
    pointStack.push(startP);
    mark[startP.row][startP.col]=true;

    //ջ���ղ���ջ��Ԫ�ز�Ϊ�����ڵ�
    while(pointStack.empty()==false){
        Point adjacentNotVisitedNode=getAdjacentNotVisitedNode(mark,pointStack.top(),m,n,endP);
        if(adjacentNotVisitedNode.row==-1){ //û�з������������ڽڵ�
            pointStack.pop(); //���ݵ���һ���ڵ�
            continue;
        }
        if(adjacentNotVisitedNode==endP){//�Խ϶̵�·�����ҵ����յ�,
            mark[adjacentNotVisitedNode.row][adjacentNotVisitedNode.col]=mark[pointStack.top().row][pointStack.top().col]+1;
            pointStack.push(endP);
            stack<Point> pointStackTemp=pointStack;
            vecPath.clear();
            while (pointStackTemp.empty()==false){
                vecPath.push_back(pointStackTemp.top());//����vecPath��ŵ�������·��
                pointStackTemp.pop();
            }
            pointStack.pop(); //���յ��ջ

            continue;
        }
        //��ջ�����÷��ʱ�־Ϊtrue
        mark[adjacentNotVisitedNode.row][adjacentNotVisitedNode.col]=mark[pointStack.top().row][pointStack.top().col]+1;
        pointStack.push(adjacentNotVisitedNode);
    }
}

int main(){
	int i,j,start_x,start_y,end_x,end_y,pathlength=0;
    int maze[18][36]={
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,1},
	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,1},
	{1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1},	
	{1,0,1,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1},
	{1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,1},
	{1,0,1,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1},
	{1,0,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1},
	{1,0,1,1,0,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1},
	{1,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,0,1},
	{1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1},
	{1,0,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1},
	{1,6,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
    for(i=0;i<18;i++)
    {
        for(j=0;j<36;j++)
        {
           if(maze[i][j]==5)
					{
						start_x=i,start_y=j;
						maze[i][j]=0;
					}
			if(maze[i][j]==6)
					{
						end_x=i,end_y=j;
						maze[i][j]=0;
					}
        }
    }
    Point startP(start_x,start_y);
    Point endP(end_x,end_y);
    stack<Point>  pointStack;
    vector<Point> vecPath;
    mazePath(maze,18,36,startP,endP,pointStack,vecPath);
	
    if(vecPath.empty()==true)
        cout<<"no right path"<<endl;
    else{
        cout<<"shortest path:";
        for(vector<Point>::reverse_iterator r_iter=vecPath.rbegin();r_iter!=vecPath.rend();++r_iter){
		
            printf("(%d,%d) ",r_iter->row,r_iter->col);
            pathlength++;
    }
	}
	cout<<endl<<"pathlength: "<<pathlength<<endl;
    getchar();
}
