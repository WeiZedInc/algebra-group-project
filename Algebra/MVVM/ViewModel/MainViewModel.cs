using Algebra.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Algebra.MVVM.ViewModel
{
    internal class MainViewModel : ObservableObject
    {
        public RelayCommand HomeViewCommand { get; set; }
        public RelayCommand InformationViewCommand { get; set; }


        public HomeViewModel HomeVM { get; set; }
        public InformationViewModel InformationVM { get; set; }

        private object _currentView;
        public object CurrentView
        {
            get { return _currentView; }
            set 
            { 
                _currentView = value;
                OnPropertyChanged();
            }
        }

        public MainViewModel()
        {
            HomeVM = new();
            InformationVM = new();
            CurrentView = HomeVM;

            HomeViewCommand = new(o =>
            {
                CurrentView= HomeVM;
            });

            InformationViewCommand = new(o =>
            {
                CurrentView = InformationVM;
            });
        }
    }
}
