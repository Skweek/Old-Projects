using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace ActorEditor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        // Actor body parts
        Image ActorHead = new Image();
        Image ActorBody = new Image();
        Image ActorLeftArm = new Image();
        Image ActorRightArm = new Image();
        Image ActorLeftLeg = new Image();
        Image ActorRightLeg = new Image();
        public int[] ActorPartsRows = new int[6];
        // End Actor body parts

        public string AppPath = Environment.CurrentDirectory + "../../../";
        Image currentspritesheet = new Image();
        System.Drawing.Bitmap selectedspriteimage = null;
        Image selector = new Image();

        public MainWindow()
        {
            InitializeComponent();
            ActorViewer.Background = Brushes.Cyan;
            currentspritesheet.Width = 128;   
            currentspritesheet.Height = 64;
            Canvas.SetTop(currentspritesheet, 0);
            Canvas.SetLeft(currentspritesheet, 0);
        }

        private void AddCanvasGuides()
        {
            Line line = new Line();
            line.Visibility = Visibility.Visible;
            line.StrokeThickness = 1;
            line.Stroke = Brushes.Black;
            line.X1 = 0;
            line.X2 = 128;
            line.Y1 = 0;
            line.Y2 = 0;
            actorLimbs.Children.Add(line);

            Line line2 = new Line();
            line2.Visibility = Visibility.Visible;
            line2.StrokeThickness = 1;
            line2.Stroke = Brushes.Black;
            line2.X1 = 0;
            line2.X2 = 128;
            line2.Y1 = 32;
            line2.Y2 = 32;
            actorLimbs.Children.Add(line2);

            Line line3 = new Line();
            line3.Visibility = Visibility.Visible;
            line3.StrokeThickness = 1;
            line3.Stroke = Brushes.Black;
            line3.X1 = 0;
            line3.X2 = 128;
            line3.Y1 = 64;
            line3.Y2 = 64;
            actorLimbs.Children.Add(line3);

            Line line4 = new Line();
            line4.Visibility = Visibility.Visible;
            line4.StrokeThickness = 1;
            line4.Stroke = Brushes.Black;
            line4.X1 = 0;
            line4.X2 = 0;
            line4.Y1 = 0;
            line4.Y2 = 64;
            actorLimbs.Children.Add(line4);

            Line line5 = new Line();
            line5.Visibility = Visibility.Visible;
            line5.StrokeThickness = 1;
            line5.Stroke = Brushes.Black;
            line5.X1 = 32;
            line5.X2 = 32;
            line5.Y1 = 0;
            line5.Y2 = 64;
            actorLimbs.Children.Add(line5);

            Line line6 = new Line();
            line6.Visibility = Visibility.Visible;
            line6.StrokeThickness = 1;
            line6.Stroke = Brushes.Black;
            line6.X1 = 64;
            line6.X2 = 64;
            line6.Y1 = 0;
            line6.Y2 = 64;
            actorLimbs.Children.Add(line6);

            Line line7 = new Line();
            line7.Visibility = Visibility.Visible;
            line7.StrokeThickness = 1;
            line7.Stroke = Brushes.Black;
            line7.X1 = 96;
            line7.X2 = 96;
            line7.Y1 = 0;
            line7.Y2 = 64;
            actorLimbs.Children.Add(line7);
        }

        private void comboBox1_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            int index = cmbActorLimbTypes.SelectedIndex;

            BitmapImage imageSource = new BitmapImage();

            switch (index)
            {
                case 0:
                    actorLimbs.Children.Clear();
                    imageSource.BeginInit();
                    imageSource.UriSource = new Uri(AppPath + "/resources/ActorArmLeft.png");
                    imageSource.EndInit();
                    currentspritesheet.Source = imageSource;
                    actorLimbs.Children.Add(currentspritesheet);
                    break;
                case 1:
                    actorLimbs.Children.Clear();
                    imageSource.BeginInit();
                    imageSource.UriSource = new Uri(AppPath + "/resources/ActorArmRight.png");
                    imageSource.EndInit();
                    currentspritesheet.Source = imageSource;
                    actorLimbs.Children.Add(currentspritesheet);
                    break;
                case 2:
                    actorLimbs.Children.Clear();
                    imageSource.BeginInit();
                    imageSource.UriSource = new Uri(AppPath + "/resources/ActorLegLeft.png");
                    imageSource.EndInit();
                    currentspritesheet.Source = imageSource;
                    actorLimbs.Children.Add(currentspritesheet);
                    break;
                case 3:
                    actorLimbs.Children.Clear();
                    imageSource.BeginInit();
                    imageSource.UriSource = new Uri(AppPath + "/resources/ActorLegRight.png");
                    imageSource.EndInit();
                    currentspritesheet.Source = imageSource;
                    actorLimbs.Children.Add(currentspritesheet);
                    break;
                case 4:
                    actorLimbs.Children.Clear();
                    imageSource.BeginInit();
                    imageSource.UriSource = new Uri(AppPath + "/resources/ActorHeadHair.png");
                    imageSource.EndInit();
                    currentspritesheet.Source = imageSource;
                    actorLimbs.Children.Add(currentspritesheet);
                    break;
                case 5:
                    actorLimbs.Children.Clear();
                    imageSource.BeginInit();
                    imageSource.UriSource = new Uri(AppPath + "/resources/ActorBody.png");
                    imageSource.EndInit();
                    currentspritesheet.Source = imageSource;
                    actorLimbs.Children.Add(currentspritesheet);
                    break;
            }
        }

        private void actorLimbs_MouseDown(object sender, MouseButtonEventArgs e)
        {
            // Get our position
            double x, y;
            x = e.GetPosition(actorLimbs).X;
            y = e.GetPosition(actorLimbs).Y;
            
            // Get it in a tile size ( multiple of 32 )
            x = Math.Floor(x / 32) * 32;
            y = Math.Floor(y / 32) * 32;

            // Draw selector
            BitmapImage imageSource = new BitmapImage();
            imageSource.BeginInit();
            imageSource.UriSource = new Uri(AppPath + "/resources/selector.png");
            imageSource.EndInit();
            selector.Source = imageSource;
            actorLimbs.Children.Remove(selector);
            Canvas.SetLeft(selector, x);
            Canvas.SetTop(selector, y);
            selector.Width = 32;
            selector.Height = 32;
            actorLimbs.Children.Add(selector);


            // Actually select the thing we are clicking
            System.Drawing.Bitmap img = new System.Drawing.Bitmap(new Uri( currentspritesheet.Source.ToString()).LocalPath);
            System.Drawing.RectangleF rect = new System.Drawing.RectangleF();
            rect.X = (float)x;
            rect.Y = (float)y;
            rect.Width = 32;
            rect.Height = 32;
            selectedspriteimage = img.Clone(rect, img.PixelFormat);

            // Convert it to Image so we can store it
            System.IO.Stream imageStream = new System.IO.MemoryStream();
            selectedspriteimage.Save(imageStream, System.Drawing.Imaging.ImageFormat.Png);
            BitmapImage bmpi = new BitmapImage();
            bmpi.BeginInit();
            bmpi.StreamSource = imageStream;
            bmpi.EndInit();

            // Which body part are we actually looking at?
            switch (cmbActorLimbTypes.SelectedIndex)
            {
                case 0:
                    ActorLeftArm.Source = bmpi;
                    ActorPartsRows[cmbActorLimbTypes.SelectedIndex] = (int)Math.Floor(y / 32);
                    break;
                case 1:
                    ActorRightArm.Source = bmpi;
                    ActorPartsRows[cmbActorLimbTypes.SelectedIndex] = (int)Math.Floor(y / 32);
                    break;
                case 2:
                    ActorLeftLeg.Source = bmpi;
                    ActorPartsRows[cmbActorLimbTypes.SelectedIndex] = (int)Math.Floor(y / 32);
                    break;
                case 3:
                    ActorRightLeg.Source = bmpi;
                    ActorPartsRows[cmbActorLimbTypes.SelectedIndex] = (int)Math.Floor(y / 32);
                    break;
                case 4:
                    ActorHead.Source = bmpi;
                    ActorPartsRows[cmbActorLimbTypes.SelectedIndex] = (int)Math.Floor(y / 32);
                    break;
                case 5:
                    ActorBody.Source = bmpi;
                    ActorPartsRows[cmbActorLimbTypes.SelectedIndex] = (int)Math.Floor(y / 32);
                    break;


            }

            // Grid lines for the sprites
            //AddCanvasGuides();
        }

        private void ActorViewer_Loaded(object sender, RoutedEventArgs e)
        {
            ActorViewer.Children.Add(ActorLeftArm);
            ActorViewer.Children.Add(ActorRightArm);
            ActorViewer.Children.Add(ActorLeftLeg);
            ActorViewer.Children.Add(ActorRightLeg);
            ActorViewer.Children.Add(ActorHead);
            ActorViewer.Children.Add(ActorBody);
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            XMLHandler.ExportActor(this);
        }
    }
}
