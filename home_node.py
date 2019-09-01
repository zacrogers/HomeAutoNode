'''
Object to represent smart home node
'''
from bs4 import BeautifulSoup
import requests

class home_node:
	def __init__(self, ip, name):
		self.ip = ip
		self.name = name
		self.num_relays = 4

	#Set relay based on old arduino code
	def set_relay_old(self, relay_num):
		try:
			requests.get('http://{}/relay{}'.format(self.ip, relay_num))

		except requests.exceptions.RequestException as e:	
			print (e)

	''''''
	def set_relay(self, relay_num, state):
		try:
			requests.get('http://{}/re{}_{}'.format(self.ip, relay_num, state))

		except requests.exceptions.RequestException as e:	
			print (e)

	# def set_all(self, state):
	# 	if state is 'on':
	# 		set_relay()


	def get_temp(self):
		text = "NC"
		try:
			temp = requests.get('http://'+self.ip+'/get_temp', timeout=3)
			if temp.status_code == 200:
				soup = BeautifulSoup(temp.text, 'html.parser')
				text = 'Inside: {}\u2103'.format(soup.text.strip())

		except requests.exceptions.RequestException as e:	
			print (e)

		return text		

#'http://192.168.20.100/relay1'