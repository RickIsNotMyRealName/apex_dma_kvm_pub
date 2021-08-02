	#include "vector.h"
    #include "imgui.h"

    bool Radar = true;
	bool teamRadar = false;
	bool enemyRadar = true;
	int xAxis_Radar = 0;
	int yAxis_Radar = 400;
	int radartype = 0;
	int width_Radar = 250;
	int height_Radar = 250;
	int distance_Radar = 400;
    #define RED ImColor(255, 0, 0)
    ImColor color = RED;
    
    static Vector RotatePoint(Vector EntityPos, Vector LocalPlayerPos, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool* viewCheck)
{
	float r_1, r_2;
	float x_1, y_1;
 
	r_1 = -(EntityPos.y - LocalPlayerPos.y);
	r_2 = EntityPos.x - LocalPlayerPos.x;
	float Yaw = angle - 90.0f;
 
	float yawToRadian = Yaw * (float)(M_PI / 180.0F);
	x_1 = (float)(r_2 * (float)cos((double)(yawToRadian)) - r_1 * sin((double)(yawToRadian))) / 20;
	y_1 = (float)(r_2 * (float)sin((double)(yawToRadian)) + r_1 * cos((double)(yawToRadian))) / 20;
 
	*viewCheck = y_1 < 0;
 
	x_1 *= zoom;
	y_1 *= zoom;
 
	int sizX = sizeX / 2;
	int sizY = sizeY / 2;
 
	x_1 += sizX;
	y_1 += sizY;
 
	if (x_1 < 5)
		x_1 = 5;
 
	if (x_1 > sizeX - 5)
		x_1 = sizeX - 5;
 
	if (y_1 < 5)
		y_1 = 5;
 
	if (y_1 > sizeY - 5)
		y_1 = sizeY - 5;
 
 
	x_1 += posX;
	y_1 += posY;
 
 
	return Vector(x_1, y_1, 0);
}

void DrawRadarHUD(int xAxis, int yAxis, int width, int height)
{
	bool out = false;
	Vector siz;
	siz.x = width;
	siz.y = height;
	Vector pos;
	pos.x = xAxis;
	pos.y = yAxis;
	float RadarCenterX = pos.x + (siz.x / 2);
	float RadarCenterY = pos.y + (siz.y / 2);
	DrawOutlineBox(pos.x, pos.y, siz.x, siz.y, ImColor(.12f, .12f, .12f, 1.f), 1.0f);
	DrawBox(pos.x, pos.y, siz.x, siz.y, 1.f, .12f, 0.12f, 0.12f, .9f, true);
	DrawLine(RadarCenterX, RadarCenterY, pos.x, pos.y, 1.f, .3f, .3f, .3f, 1.f);
	DrawLine(RadarCenterX, RadarCenterY, pos.x + siz.x, pos.y, 1.f, .3f, .3f, .3f, 1.f);
	DrawLine(pos.x, RadarCenterY, pos.x + siz.x, RadarCenterY, 1.f, .3f, .3f, .3f, 1.f);
	DrawLine(RadarCenterX, RadarCenterY, RadarCenterX, pos.y + siz.y, 1.f, .3f, .3f, .3f, 1.f);
	DrawCircle(RadarCenterX, RadarCenterY, 2.f, 1.f, .3f, .3f, .3f, 1.f, true);
}
void DrawRadarPoint( Player Enemy, Player LocalPlayer, int xAxis, int yAxis, int width, int height, ImColor color)
{
	bool out = false;
	Vector siz;
	siz.x = width;
	siz.y = height;
	Vector pos;
	pos.x = xAxis;
	pos.y = yAxis;
	bool ck = false;
	Vector single = RotatePoint(Enemy.origin, LocalPlayer.origin, pos.x, pos.y, siz.x, siz.y, LocalPlayer.YAW.y, 2.f, &ck);
	if (Enemy.Distance >= 0.f && Enemy.Distance < distance_Radar)
	{
		if (radartype == 0)
			DrawShadowText(std::to_string((int)Player.Distance), 11, single.x, single.y, color);
		else
			DrawCircle(single.x, single.y, 5, 1, color, true);
 
	}
}

void drawloop()
{
 
	if (Radar)
		DrawRadarHUD(xAxis_Radar,yAxis_Radar, width_Radar,height_Radar);
 
	if (Radar)
		{
			if checkSetting(teamRadar, enemyRadar)
			{
				DrawRadarPoint( enemy, player, xAxis_Radar, yAxis_Radar, width_Radar, height_Radar, color);
			}
		}
 
}