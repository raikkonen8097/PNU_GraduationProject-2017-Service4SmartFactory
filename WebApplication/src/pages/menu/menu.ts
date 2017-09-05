import { Component, ViewChild } from '@angular/core';
import { Nav, NavController, NavParams } from 'ionic-angular';

import { ControlMachinePage } from '../control-machine/control-machine';
import { LoginPage } from '../login/login'
import { Storage } from '@ionic/storage';

import { AuthProvider } from '../../providers/auth/auth'

@Component({
  selector: 'page-menu',
  templateUrl: 'menu.html',
})
export class MenuPage {
  @ViewChild(Nav) nav: Nav;

  rootPage: any = ControlMachinePage;

  user: string;
  accessLevel: string;

  pages: Array<{ title: string, component: any }>;

  constructor(public navCtrl: NavController, public navParams: NavParams,
    public authService: AuthProvider, public storage: Storage) {// used for an example of ngFor and navigation

  }

  ionViewDidLoad() {
    this.pages = [
      { title: '관제', component: ControlMachinePage }
    ];
    this.getUser();
    this.getAccessLevel();
  }

  openPage(page) {
    // Reset the content nav to have just this page
    // we wouldn't want the back button to show in this scenario
    this.nav.setRoot(page.component);
  }

  logout() {
    this.authService.logout();
    this.navCtrl.setRoot(LoginPage);

  }

  getUser() {
    this.storage.get('email').then(email => {
      this.user = email;
    });
  }
  getAccessLevel() {
    this.storage.get('accessLevel').then(accessLevel => {
      this.accessLevel = accessLevel;
    });
  }
}