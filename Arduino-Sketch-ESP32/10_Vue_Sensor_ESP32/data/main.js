const ESP32 = {
    data() {
      return {
        temperaturaDato: 25,
        humedadDato: 50,
        buttonStatus: 0,
        
      }
    },
    methods: {

      buttonOn(){
        buttonStatus = 1; 
        console.log("Led is ON")
        send_data()
      },

      buttonOff(){
        buttonStatus = 0;
        console.log("Led is OFF")
        send_data()
      },
      
      send_data(){
        var full_data = '{"Led" :'+buttonStatus+'}'
        connection.send(full_data)
      }
      
    },
  }
  
  var connection = new WebSocket('ws://'+location.hostname+':81/')
  connection.onmessage = function(event){
  
  temperaturaDato = data.temp
  humedadDato = data.hum
  
  var full_data = event.data
  console.log(full_data)
  var data = JSON.parse(full_data)
}


  
  Vue.createApp(ESP32).mount('#esp32')