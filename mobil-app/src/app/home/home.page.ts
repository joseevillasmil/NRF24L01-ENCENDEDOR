import { Component } from '@angular/core';
import {BluetoothSerial} from "@ionic-native/bluetooth-serial/ngx";

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage {

  mac = '';
  constructor(private bt: BluetoothSerial) {}

  encender(device: string) {
    this.bt.write(device + 'A');
  }

  apagar(device: string) {
    this.bt.write(device + 'O');
  }

  conectar() {
    this.bt.list().then(
        data => {
          this.mac = data[0].address;
          this.bt.connect(this.mac).subscribe(
              () => {
                alert('Conectado');
              }
          );
        }
    );
  }

}
