extends Node

const basepath = "./CanvasLayer/Control/VBoxContainer/"
@onready var playerNode:Droplet = get_node("./Node2D/Droplet")
@onready var speedLabel:Label = get_node("./CanvasLayer/Control/SpeedLabel")
var runInput:Control = null

# Called when the node enters the scene tree for the first time.
func _ready():
	runInput = get_node(basepath+"MaxRunSpeedContainer")
	if runInput:
		runInput.updated_run_speed.connect(update_max_player_speed)
	
	var maxAccelInput = get_node(basepath+"RunAccelarationContainer")
	if maxAccelInput:
		maxAccelInput.updated_run_accelartion.connect(update_run_acceleration)
	
	var baseRunSpeedInput = get_node(basepath+"BaseRunSpeedContainer")
	if baseRunSpeedInput:
		baseRunSpeedInput.updated_base_run_speed.connect(update_base_run_speed)
		
	var gravityInput = get_node(basepath+"GravityContainer")
	if gravityInput:
		gravityInput.updated_gravity.connect(update_gravity)
		
	var logDragInput = get_node(basepath+"LogDragContainer")
	if logDragInput:
		logDragInput.updated_logdrag.connect(update_log_drag)
		

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if speedLabel && playerNode:
		speedLabel.text = str(playerNode.velocity)

func update_max_player_speed(value:float):
	if playerNode && runInput:
		print(value, "updating player speed")
		playerNode.MAX_RUN_SPEED = value
		
		
func update_run_acceleration(value:float):
	if playerNode:
		print(value, "updating player accelertation")
		playerNode.RUN_ACCELERATION = value

func update_base_run_speed(value:float):
	if playerNode:
		print(value, "updating player base run speed")
		playerNode.BASE_RUN_SPEED = value
		
func update_gravity(value:float):
	if playerNode:
		print(value, "updating player gravity")
		playerNode.GRAVITY = value
		
		
func update_log_drag(value:float):
	if playerNode:
		print(value, "updating player log drag")
		playerNode.LOG_DRAG = value
		

		
	
