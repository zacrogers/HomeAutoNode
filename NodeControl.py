from kivy.app import App

from kivy.uix.button import Button
from kivy.uix.label import Label
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.textinput import TextInput
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.gridlayout import GridLayout

from home_node import home_node as node

class MainWindow(BoxLayout):
    pass

class NodeControl(App):
	node = node('192.168.20.100', 'bedroom')

	def build(self):
		return MainWindow()

if __name__=="__main__":
    NodeControl().run()
