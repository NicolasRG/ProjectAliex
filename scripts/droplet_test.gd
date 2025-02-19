extends Droplet


# Called when the node enters the scene tree for the first time.
func _ready():
	var children:Array = get_children(true)
	print(children)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
