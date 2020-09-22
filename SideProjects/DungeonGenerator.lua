--Generates a map with rooms, corridors and doors and then writes it to a text-file 

function Main()
  local localMainMap = {}
  
  local localMainMapWidth, localMainMapHeight = 50, 50
  
  GenerateMap(localMainMap, localMainMapWidth, localMainMapHeight) 
  
  --Write the map to file
  local f = io.open("map.txt", "w")
  for i = 1, localMainMapHeight do
    for j = 1, localMainMapWidth do
      f:write(localMainMap[i][j])
    end
  end
end

Rect = {}
Rect.__index = Rect

function Rect:create(x, y, w, h)
  local localRect = {}
  setmetatable(localRect, Rect)
  localRect.x1 = x
  localRect.y1 = y
  localRect.x2 = x+w
  localRect.y2 = y+h
  return localRect
end

function Rect:center()
  local localCenterX = math.floor((self.x1 + self.x2)/2)
  local localCenterY = math.floor((self.y1 + self.y2)/2)
  return localCenterX, localCenterY
end

function Rect:intersect(other)
  return (self.x1 <= other.x2 and self.x2 >= other.x1 and self.y1 <= other.y2 and self.y2 >= other.y1)
end

function GenerateRoom(map, newRoom)
  for x = newRoom.x1 + 1, newRoom.x2 do
      for y = newRoom.y1 + 1, newRoom.y2 do
        map[x][y] = "."
      end
    end
  end

function GenerateHorizontalTunnel(map, x1, x2, y)
  for x = math.min(x1, x2), math.max(x1, x2)+1 do
    map[x][y] = "."
  end
end

function GenerateVerticalTunnel(map, y1, y2, x)
  for y = math.min(y1, y2), math.max(y1,y2)+1 do
    map[x][y] = "."
  end
end

function GenerateDoors(map, mapWidth, mapHeight)
  for x = 1, mapWidth do
     for y = 1, mapHeight do
       --Find a spot where there's walls both to the north and south: Horizontal door
       if (map[x][y] == "." and map[x+1][y] == "#" and map[x-1][y] == "#" and map[x][y+1] == "." and map[x][y-1] == ".") then 
         --Check if this spot is clear to the NE, E, SE or NW, W, SW
         if (map[x+1][y+1] ~= "#" and map[x][y+1] ~= "#" and map[x-1][y+1] ~= "#") or (map[x+1][y-1] ~= "#" and map[x][y-1] ~= "#" and map[x-1][y-1] ~= "#") then
           map[x][y] = "+"
         end
       --Find a spot where there's walls both to the east and west: Vertical door
     elseif (map[x][y] == "." and map[x][y+1] == "#" and map[x][y-1] == "#" and map[x+1][y] == "." and map[x-1][y] == ".") then
       --Check if this spot is clear to the NE, N, NW or SE, S, SW
         if (map[x+1][y+1] ~= "#" and map[x+1][y] ~= "#" and map[x+1][y-1] ~= "#") or (map[x-1][y+1] ~= "#" and map[x-1][y] ~= "#" and map[x-1][y-1] ~= "#") then
           map[x][y] = "+"
         end
       end
     end
  end
end

function GenerateMap(map, mapWidth, mapHeight)
  --Variables for tweaking
  local localGenMapRoomMaxSize, localGenMapRoomMinSize, localGenMapMaxRooms, localGenMapNumRooms = 15, 6, 30, 0
  local localGenMapRooms = {}
  
  for x = 1, mapWidth do
    map[x] = {}
    for y = 1, mapHeight do
      if y == mapHeight then
        map[x][y] = "#\n"
      else
        map[x][y] = "#"
      end
    end
  end
  
  math.randomseed(os.time())
  for i = 1, localGenMapMaxRooms do
    local w = math.random(localGenMapRoomMinSize, localGenMapRoomMaxSize)
    local h = math.random(localGenMapRoomMinSize, localGenMapRoomMaxSize)
    
    local x = math.random(1, mapWidth - w-1)
    local y = math.random(1, mapHeight - h-1)
    
    local localNewRoom = Rect:create(x, y, w, h)
    
    local localFailed = false
    
    for i, otherRoom in ipairs(localGenMapRooms) do
      if localNewRoom:intersect(otherRoom) then
        localFailed = true
        break
      end
    end
    
    if not localFailed then
      GenerateRoom(map, localNewRoom)
      
      local localNewX, localNewY = localNewRoom:center()
      
      if localGenMapNumRooms ~= 0 then
        local localPrevX, localPrevY = localGenMapRooms[localGenMapNumRooms]:center()
        
        GenerateHorizontalTunnel(map, localPrevX, localNewX, localPrevY)
        GenerateHorizontalTunnel(map, localPrevX, localNewX, localNewY)
        GenerateVerticalTunnel(map, localPrevY, localNewY, localPrevX)
        GenerateVerticalTunnel(map, localPrevY, localNewY, localNewX)
      end
      
      table.insert(localGenMapRooms, localNewRoom)
      localGenMapNumRooms = localGenMapNumRooms + 1
    end
  end
  
  GenerateDoors(map, mapWidth, mapHeight)
  
end

Main()