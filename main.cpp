#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;

#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

Uint32 buffer[screenHeight][screenWidth];

int main(int argc, char* argv[])
{
double posX=22,posY=11.5;
double dirX=-1,dirY=0;
double planeX=0,planeY=0.66;

double time=0,oldTime=0;

std::vector<Uint32> texture[8];
for(int i=0;i<8;i++) texture[i].resize(texWidth*texHeight);

screen(screenWidth,screenHeight,0,"Raycaster");

unsigned long tw,th;
loadImage(texture[0],tw,th,"pics/eagle.png");
loadImage(texture[1],tw,th,"pics/redbrick.png");
loadImage(texture[2],tw,th,"pics/purplestone.png");
loadImage(texture[3],tw,th,"pics/greystone.png");
loadImage(texture[4],tw,th,"pics/bluestone.png");
loadImage(texture[5],tw,th,"pics/mossy.png");
loadImage(texture[6],tw,th,"pics/wood.png");
loadImage(texture[7],tw,th,"pics/colorstone.png");

while(!done())
{

for(int x=0;x<w;x++)
{
double cameraX=2*x/(double)w-1;
double rayDirX=dirX+planeX*cameraX;
double rayDirY=dirY+planeY*cameraX;

int mapX=int(posX);
int mapY=int(posY);

double sideDistX,sideDistY;

double deltaDistX=(rayDirX==0)?1e30:fabs(1/rayDirX);
double deltaDistY=(rayDirY==0)?1e30:fabs(1/rayDirY);

int stepX,stepY;

int hit=0;
int side;

if(rayDirX<0)
{
stepX=-1;
sideDistX=(posX-mapX)*deltaDistX;
}
else
{
stepX=1;
sideDistX=(mapX+1-posX)*deltaDistX;
}

if(rayDirY<0)
{
stepY=-1;
sideDistY=(posY-mapY)*deltaDistY;
}
else
{
stepY=1;
sideDistY=(mapY+1-posY)*deltaDistY;
}

while(hit==0)
{
if(sideDistX<sideDistY)
{
sideDistX+=deltaDistX;
mapX+=stepX;
side=0;
}
else
{
sideDistY+=deltaDistY;
mapY+=stepY;
side=1;
}

if(worldMap[mapX][mapY]>0) hit=1;
}

double perpWallDist;

if(side==0) perpWallDist=(sideDistX-deltaDistX);
else perpWallDist=(sideDistY-deltaDistY);

int lineHeight=int(h/perpWallDist);

int drawStart=-lineHeight/2+h/2;
if(drawStart<0) drawStart=0;

int drawEnd=lineHeight/2+h/2;
if(drawEnd>=h) drawEnd=h-1;

int texNum=worldMap[mapX][mapY]-1;

double wallX;

if(side==0) wallX=posY+perpWallDist*rayDirY;
else wallX=posX+perpWallDist*rayDirX;

wallX-=floor(wallX);

int texX=int(wallX*texWidth);

if(side==0 && rayDirX>0) texX=texWidth-texX-1;
if(side==1 && rayDirY<0) texX=texWidth-texX-1;

double step=1.0*texHeight/lineHeight;

double texPos=(drawStart-h/2+lineHeight/2)*step;

for(int y=drawStart;y<drawEnd;y++)
{
int texY=int(texPos)&(texHeight-1);
texPos+=step;

Uint32 color=texture[texNum][texHeight*texY+texX];

if(side==1) color=(color>>1)&8355711;

buffer[y][x]=color;
}

}

/* ---------- MINIMAP ---------- */

int scale=6;
int offsetX=10;
int offsetY=10;

for(int my=0;my<mapHeight;my++)
for(int mx=0;mx<mapWidth;mx++)
{
Uint32 color;

if(worldMap[mx][my]>0)
color=RGBtoINT(ColorRGB(255,255,255));
else
color=RGBtoINT(ColorRGB(0,0,0));

for(int py=0;py<scale;py++)
for(int px=0;px<scale;px++)
buffer[offsetY+my*scale+py][offsetX+mx*scale+px]=color;
}

int px=int(posX*scale)+offsetX;
int py=int(posY*scale)+offsetY;

for(int y=-2;y<=2;y++)
for(int x=-2;x<=2;x++)
buffer[py+y][px+x]=RGBtoINT(ColorRGB(255,0,0));

for(int i=0;i<10;i++)
{
int dx=int((posX+dirX*i*0.3)*scale)+offsetX;
int dy=int((posY+dirY*i*0.3)*scale)+offsetY;

buffer[dy][dx]=RGBtoINT(ColorRGB(0,255,0));
}

/* ----------------------------- */

drawBuffer(buffer[0]);

for(int y=0;y<h;y++)
for(int x=0;x<w;x++)
buffer[y][x]=0;

oldTime=time;
time=getTicks();

double frameTime=(time-oldTime)/1000.0;

print(1.0/frameTime);

redraw();

double moveSpeed=frameTime*5.0;
double rotSpeed=frameTime*3.0;

readKeys();

if(keyDown(SDLK_UP))
{
if(!worldMap[int(posX+dirX*moveSpeed)][int(posY)]) posX+=dirX*moveSpeed;
if(!worldMap[int(posX)][int(posY+dirY*moveSpeed)]) posY+=dirY*moveSpeed;
}

if(keyDown(SDLK_DOWN))
{
if(!worldMap[int(posX-dirX*moveSpeed)][int(posY)]) posX-=dirX*moveSpeed;
if(!worldMap[int(posX)][int(posY-dirY*moveSpeed)]) posY-=dirY*moveSpeed;
}

if(keyDown(SDLK_RIGHT))
{
double oldDirX=dirX;
dirX=dirX*cos(-rotSpeed)-dirY*sin(-rotSpeed);
dirY=oldDirX*sin(-rotSpeed)+dirY*cos(-rotSpeed);

double oldPlaneX=planeX;
planeX=planeX*cos(-rotSpeed)-planeY*sin(-rotSpeed);
planeY=oldPlaneX*sin(-rotSpeed)+planeY*cos(-rotSpeed);
}

if(keyDown(SDLK_LEFT))
{
double oldDirX=dirX;
dirX=dirX*cos(rotSpeed)-dirY*sin(rotSpeed);
dirY=oldDirX*sin(rotSpeed)+dirY*cos(rotSpeed);

double oldPlaneX=planeX;
planeX=planeX*cos(rotSpeed)-planeY*sin(rotSpeed);
planeY=oldPlaneX*sin(rotSpeed)+planeY*cos(rotSpeed);
}

if(keyDown(SDLK_ESCAPE)) break;

}

return 0;
}
