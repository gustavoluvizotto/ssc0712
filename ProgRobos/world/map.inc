# map.inc - useful setup for a floorplan bitmap
# Authors: Richard Vaughan
# $Id$

define floorplan model
(
  color "gray30" # sombre, sensible, artistic
  boundary 1 # most maps will need a bounding box
  gui_nose 0 # if 1, draw a nose on the model showing its heading (positive X axis)
  gui_grid 0 # if 1, draw a scaling grid over the model
  gui_move 0
  gui_outline 0
  gripper_return 0
  fiducial_return 0 # if non-zero, this model is detected by fiducialfinder sensors. The non-zero integer value is used as the fiducial ID
  ranger_return 0.5 # Se esse modelo pode ser detectado por sensores ranger. Se -1, é transparente. Não sei pq o padrão é 0.5. No arquivo pioneer.inc diz: 'reflects sonar beams' para esse valor
  obstacle_return 1 # if 1, this model can collide with other models that have this property set
)

define zone model
(
  color	"orange"
  size [ 4 4 0.01 ]

  gui_nose 0
  gui_grid 0
  gui_move 1
  gui_outline 0

  obstacle_return 0 # insensible to collision and range sensors
  ranger_return -1  # transparent to range sensors
)

