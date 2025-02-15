extends HBoxContainer
@onready var labelTextBox = $label
@onready var slider:Slider = $slider
@onready var currentTextBox = $currentval
@onready var test = get_node("/root/MainGame")

signal updated_logdrag(newValue)
#expose hookin to trigger

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.
func _on_slider_value_changed(value):
	if test :
		updated_logdrag.emit(value)
	currentTextBox.text = str(value)
	slider.release_focus()
